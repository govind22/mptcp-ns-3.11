/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include "ns3/gtk-config-store.h"

#include "FtpServer.h"
#include "FtpClient.h"

#include <time.h>
using namespace ns3;




// Basic parameters
int serverCount_total = 64;
int portCount_perSwitch = 16;

bool ecmp = true;
bool noCoreSwitches = true;

char* linkRate = (char*)"1Gbps";
char* linkDelay = (char*)"25us";

int bgFlowCount = 64;
int bgFlowByteCount = 10 * 1024 * 1024;
int smFlowCount = 0;
int smFlowByteCount = 50 * 1024;
int qFlowCount = 32;
int qFlowByteCount = 2 * 1024;
int qFlowPartCount = 50;
Time qFlowInterval = MilliSeconds(100);

Time simStartTime = Seconds(0.001);
Time simStopTime = Seconds(0.100);
Time progressCheckInterval = MilliSeconds(10);
bool netanim = false;


// Derived parameters
int podCount_total = serverCount_total * 4 / (portCount_perSwitch * portCount_perSwitch) ;
int serverCount_perPod = serverCount_total / podCount_total;
int serverCount_perTorSwitch = portCount_perSwitch / 2;
int torSwitchCount_perPod = serverCount_perPod / portCount_perSwitch * 2;
int aggSwitchCount_perPod = torSwitchCount_perPod;
int torSwitchCount_total = podCount_total * torSwitchCount_perPod;
int aggSwitchCount_total = torSwitchCount_total;
int coreSwitchCount_total = noCoreSwitches ? 0 : aggSwitchCount_total / 2;
int switchCount_total = torSwitchCount_total + aggSwitchCount_total + coreSwitchCount_total;

std::map<int, Ipv4Address> nodeAddresses;
std::map<int, int> flowCounts;
std::set<int> flowCountSamples;
int bgFlowID = 0;
int smFlowID = 0;
int qFlowID = 0;

// Set of nodes
NodeContainer servers;
NodeContainer torSwitches;
NodeContainer aggSwitches;
NodeContainer coreSwitches;

NS_LOG_COMPONENT_DEFINE ("FatTree");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ipv4InterfaceContainer connectNodes (Ptr<Node> node1, Ptr<Node> node2, char* linkRate, char* linkDelay, Ipv4AddressHelper addressHelper, bool pcapTrace = false) 
{
  NodeContainer nodePair;
  nodePair.Add(node1);
  nodePair.Add(node2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue (linkRate));
  pointToPoint.SetChannelAttribute ("Delay", StringValue (linkDelay));
  pointToPoint.SetQueue("ns3::DropTailQueue");
  if (pcapTrace) pointToPoint.EnablePcap("trace", nodePair);

  NetDeviceContainer devices = pointToPoint.Install (nodePair);
  Ipv4InterfaceContainer interfaces = addressHelper.Assign (devices);
  return interfaces;
}

void setLocation(Ptr<Node> node, int x, int y)
{
  Ptr<ConstantPositionMobilityModel> nodeLoc =  node->GetObject<ConstantPositionMobilityModel> ();
  if (nodeLoc == 0)
  {
    nodeLoc = CreateObject<ConstantPositionMobilityModel> ();
    node->AggregateObject (nodeLoc);
  }
  Vector nodeVec (x, y, 0);
  nodeLoc->SetPosition(nodeVec);
}


void onFlowStart(Ptr<Node> node)
{
  flowCounts[node->GetId()]++; 
  //if (node->GetId() == 0) std::cerr << Now() << ": Inc -> " << flowCounts[node->GetId()] << "\n";
}

void onFlowStop(Ptr<Node> node)
{
  flowCounts[node->GetId()]--;
  //if (node->GetId() == 0) std::cerr << Now() << ": Dec -> " << flowCounts[node->GetId()] << "\n";
}

void startFlow(Ptr<Node> srcNode, Ptr<Node> dstNode, uint16_t port, uint64_t data, Time startTime, std::string tag, int id, void (*stopcallback)(Ptr<Node>))
{
  NodeContainer nodePair;
  nodePair.Add(srcNode);
  nodePair.Add(dstNode);

  Ptr<FtpServer> ftpServer = CreateObject<FtpServer>();
  ftpServer->Configure(data, port, startTime, true);
  ftpServer->SetTag(tag, id);
  ftpServer->SetCallBack(&onFlowStart, stopcallback);
  ftpServer->SetStartTime(startTime + Seconds(0.001));
  ftpServer->SetStopTime(simStopTime - Seconds(0.000001));
  dstNode->AddApplication(ftpServer);
  
  Address ftpServerAddress(InetSocketAddress(nodeAddresses[dstNode->GetId()], port));

  Ptr<FtpClient> ftpClient = CreateObject<FtpClient>();
  ftpClient->Configure(ftpServerAddress, data);
  ftpClient->SetTag(tag, id);
  ftpClient->SetCallBack(&onFlowStart, &onFlowStop);
  ftpClient->SetStartTime(startTime + Seconds(0.001));
  srcNode->AddApplication(ftpClient);
}

void startFlow(Ptr<Node> srcNode, Ptr<Node> dstNode, uint16_t port, uint64_t data, Time startTime, std::string tag = "Flow", int id = -1)
{
  startFlow(srcNode, dstNode, port, data, startTime, "X", -1, NULL);
}

void onBGFlowCompletion(Ptr<Node>); 

void startBGFlow(Time startTime = Now())
{
  UniformVariable bgNodeRnd;   
  UniformVariable bgJitterRnd;

  int serverID = bgNodeRnd.GetInteger(0, serverCount_total-1); 
  int otherServerID;
  Time startTime1 = startTime + Seconds(bgJitterRnd.GetValue(0,0.001));
  while ((otherServerID = bgNodeRnd.GetInteger(0, serverCount_total-1)) == serverID);

  std::cerr << "\t\tSetting up BG flow "<< bgFlowID <<" between servers " << serverID << " and " << otherServerID <<" at "<< startTime1.GetSeconds() << "s\n";
  startFlow(servers.Get(serverID), servers.Get(otherServerID), 10000 + bgFlowID % 5000, bgFlowByteCount, startTime1 , "BG", bgFlowID, &onBGFlowCompletion); 
  bgFlowID++;
}

void onBGFlowCompletion(Ptr<Node> node) 
{
  onFlowStop(node); 
  startBGFlow();
}


void onSMFlowCompletion(Ptr<Node>);

void startSMFlow(Time startTime = Now())
{
  UniformVariable smNodeRnd;   
  UniformVariable smJitterRnd;

  int serverID = smNodeRnd.GetInteger(0, serverCount_total-1); 
  int otherServerID;
  Time startTime1 = startTime + Seconds(smJitterRnd.GetValue(0,0.001));
  while ((otherServerID = smNodeRnd.GetInteger(0, serverCount_total-1)) == serverID);

  std::cerr << "\t\tSetting up SM flow "<< smFlowID <<" between servers " << serverID << " and " << otherServerID <<" at "<< startTime1.GetSeconds() << "s\n";
  startFlow(servers.Get(serverID), servers.Get(otherServerID), 20000 + smFlowID % 5000, smFlowByteCount, startTime1 , "SM", smFlowID, &onSMFlowCompletion ); 
  smFlowID++;
}

void onSMFlowCompletion(Ptr<Node> node)  
{
  onFlowStop(node); 
}

void onQFlowCompletion(Ptr<Node> node) 
{
  onFlowStop(node); 
}

void startQFlow( Time startTime = Now(), int concurrentFlowCount = 1)
{
  UniformVariable qNodeRnd;   
  UniformVariable qJitterRnd;
  
  std::set<int> usedServerIDs; 
  //int flowsWithServer0 = 0; 
  for (int i = 0; i < concurrentFlowCount; i++)
  {
      Time startTime1 = startTime + Seconds(qJitterRnd.GetValue(0,0.001));
      int serverID;
      while (usedServerIDs.count(serverID = qNodeRnd.GetInteger(0, serverCount_total-1)) > 0); 
      //if (serverID == 0) flowsWithServer0+= qFlowPartCount;
      usedServerIDs.insert(serverID);
      std::cerr << "\t\tSetting up Q(" << qFlowPartCount <<") flow "<< qFlowID <<" to server " << serverID << " at "<< startTime.GetSeconds() << "s\n";
      
      std::set <int> usedOtherServerIDs;
      usedOtherServerIDs.insert(serverID);

      for (int p = 0; p < qFlowPartCount; p++) 
      {
        Time startTime2 = startTime1 + Seconds(qJitterRnd.GetValue(0,0.001));
        
        int otherServerID;
        while (usedOtherServerIDs.count(otherServerID = qNodeRnd.GetInteger(0, serverCount_total-1)) > 0);
         
        startFlow(servers.Get(otherServerID), servers.Get(serverID), 30000 + (qFlowID * 100 + p) % 10000, qFlowByteCount, startTime2, "Q", qFlowID * 100 + p, &onQFlowCompletion ); 
        usedOtherServerIDs.insert(otherServerID);
        //if (otherServerID == 0) flowsWithServer0+= 1;
      }
      
      qFlowID++;
  }
  //std::cerr << "\t\t\tFlows with Server 0 = " << flowsWithServer0 <<"\n";
}


void setProgressTimer()
{
  //if (Now().GetMilliSeconds() % 10 == 0) 
  std::cerr << "Time: Simulation = " << std::setw(5) << Now().GetSeconds() << "s, Real: " << std::setw(5) << clock()/ CLOCKS_PER_SEC << "s\n";
  //std::cerr << "Server 0 has " << flowCounts[servers.Get(0)->GetId()] << " flows\n";
  Simulator::Schedule(progressCheckInterval, &setProgressTimer);
}

//////////////////////////////////////////////////////////////////////////////////

int main (int argc, char *argv[])
{
  
  //int nodeCount_total = serverCount_total + switchCount_total;
  
  std::cerr << "Servers  = " << serverCount_total << "\n";
  std::cerr << "Pods     = " << podCount_total << "\n";
  std::cerr << "Switches = " << torSwitchCount_total << " + " << aggSwitchCount_total << " + " << coreSwitchCount_total << " = " << switchCount_total << "\n"; 

  // Other parameters
  std::string animFile("fat-tree.tr");  // Name of file for animation output  


  // Initial Configurations
  bool set_successful = true;

  set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::SegmentSize",UintegerValue(1460));
  set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::InitialCwnd",UintegerValue(2));
  set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::DelAckCount",UintegerValue(1));
  set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::ConnTimeout",TimeValue(Seconds(0.02)));
  set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::ConnCount",UintegerValue(0));
  set_successful &= Config::SetDefaultFailSafe("ns3::TcpL4Protocol::SocketType",StringValue("ns3::TcpNewReno"));
  set_successful &= Config::SetDefaultFailSafe("ns3::RttEstimator::MinRTO",TimeValue(Seconds(0.01)));
  set_successful &= Config::SetDefaultFailSafe("ns3::DropTailQueue::Mode",EnumValue(ns3::DropTailQueue::PACKETS));
  set_successful &= Config::SetDefaultFailSafe("ns3::DropTailQueue::MaxPackets",UintegerValue(100));
  
  if (ecmp) 
  {
    set_successful &= Config::SetDefaultFailSafe("ns3::Ipv4GlobalRouting::RandomEcmpRouting", BooleanValue(true));
  } 
  if (!set_successful) 
  {
    std::cerr << "Error: Could not set defaults" << std::endl;
    return 0;
  }

  // Generating the nodes
  servers.Create(serverCount_total);
  torSwitches.Create(torSwitchCount_total);
  aggSwitches.Create(aggSwitchCount_total);
  coreSwitches.Create(coreSwitchCount_total);
  
  NodeContainer allNodes(servers, torSwitches, aggSwitches, coreSwitches);

  // Setup Internet stack in the nodes
  InternetStackHelper stack;
  stack.Install(allNodes);
 
  // Connect the ToR switches to servers
  int podID, torSwitchID, aggSwitchID, coreSwitchID, serverID;
  std::cerr << "Generating topology..."<<"\n";
  std::cerr << "\tConnecting servers to ToR switches..."<<"\n";
  for (torSwitchID = 0; torSwitchID < torSwitchCount_total; torSwitchID++)
  {
    Ipv4AddressHelper torAddressHelper;
    char *torBaseAddress = (char *) malloc(sizeof (char) * 20);
    sprintf(torBaseAddress,"10.%d.0.0", torSwitchID); 
    torAddressHelper.SetBase (torBaseAddress, "255.255.255.0");
    for (serverID = torSwitchID * serverCount_perTorSwitch; serverID < (torSwitchID + 1) * serverCount_perTorSwitch; serverID++) 
    {
      Ipv4Address address = connectNodes(torSwitches.Get(torSwitchID), servers.Get(serverID), linkRate, linkDelay, torAddressHelper).GetAddress(1);
      nodeAddresses[servers.Get(serverID)->GetId()] = address;
      torAddressHelper.NewNetwork(); 
    }
  }

  // Connect aggregate switches to ToR switches
  std::cerr << "\tConnecting ToR switches to aggregate switches..."<<"\n";
  for (podID = 0; podID < podCount_total; podID++) 
  {
    for (aggSwitchID = podID * aggSwitchCount_perPod; aggSwitchID < (podID + 1) * aggSwitchCount_perPod; aggSwitchID++)
    {
      Ipv4AddressHelper aggAddressHelper;
      char *aggBaseAddress = (char *) malloc(sizeof (char) * 20);
      sprintf(aggBaseAddress,"20.%d.0.0", aggSwitchID); 
      aggAddressHelper.SetBase (aggBaseAddress, "255.255.255.0");
      for (torSwitchID = podID * torSwitchCount_perPod; torSwitchID < (podID + 1) * torSwitchCount_perPod; torSwitchID++)
      {
        connectNodes(aggSwitches.Get(aggSwitchID), torSwitches.Get(torSwitchID), linkRate, linkDelay, aggAddressHelper);
        aggAddressHelper.NewNetwork(); 
      }
    }
  }

  // Connect aggregate switches to core switches
  std::cerr << "\tConnecting aggregate switches to core switches..."<<"\n";
  for (coreSwitchID = 0; coreSwitchID < coreSwitchCount_total; coreSwitchID++)
  {
    Ipv4AddressHelper coreAddressHelper;
    char *coreBaseAddress = (char *) malloc(sizeof (char) * 20);
    sprintf(coreBaseAddress,"30.%d.0.0", coreSwitchID); 
    coreAddressHelper.SetBase (coreBaseAddress, "255.255.255.0");
    for (aggSwitchID = coreSwitchID - aggSwitchCount_total; aggSwitchID < aggSwitchCount_total; aggSwitchID+=aggSwitchCount_perPod)
    {
      if (aggSwitchID < 0) continue; 
      connectNodes(coreSwitches.Get(coreSwitchID), aggSwitches.Get(aggSwitchID),  linkRate, linkDelay, coreAddressHelper);
      coreAddressHelper.NewNetwork();  
    }
  }
  //Config::Connect("/NodeList/*/DeviceList/*/$ns3::PointToPointNetDevice/TxQueue", 

  // Setup routing table with ECMP
  std::cerr << "Setting up routing tables..."<<"\n";
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  // Setup node locations for animation
  std::cerr << "Setting up locations for animation..." << "\n";  
  for (serverID = 0; serverID < serverCount_total; serverID++)
  {
    setLocation(servers.Get(serverID), (serverID + 0.5) * 10 * (serverCount_total / serverCount_total), 400 );
  }
  for (torSwitchID = 0; torSwitchID < torSwitchCount_total; torSwitchID++)
  {
    setLocation(torSwitches.Get(torSwitchID), (torSwitchID + 0.5) * 10 * (serverCount_total / torSwitchCount_total), 300);
  }
  for (aggSwitchID = 0; aggSwitchID < aggSwitchCount_total; aggSwitchID++)
  {
    setLocation(aggSwitches.Get(aggSwitchID), (aggSwitchID + 0.5) * 10 * (serverCount_total / aggSwitchCount_total), 200);
  }
  for (coreSwitchID = 0; coreSwitchID < coreSwitchCount_total; coreSwitchID++)
  {
    setLocation(coreSwitches.Get(coreSwitchID), (coreSwitchID + 0.5) * 10 * (serverCount_total / coreSwitchCount_total), 100);
  }

  // Setup traffic
  std::cerr << "Setting up traffic..." << "\n";
  
  std::cerr << "\tSetting up "<< bgFlowCount<<" long background flows..." << "\n";
  for (int bgFlowID = 0; bgFlowID < bgFlowCount; bgFlowID++) 
  {
    startBGFlow(simStartTime);
  } 

  std::cerr << "\tSetting up " << smFlowCount << " short message flows..." << "\n";
  for (int smFlowID = 0; smFlowID < smFlowCount; smFlowID++)
  {
    //startSMFlow(simStartTime);
  }

  std::cerr << "\tSetting up parition/aggregate query flows every "<< qFlowInterval.GetMilliSeconds() <<"ms..." << "\n";
  for (Time t = simStartTime /*+ qFlowInterval*/; t < simStopTime/*- qFlowInterval*/; t = t + qFlowInterval)
  { 
    startQFlow(t, qFlowCount);
  }


  /*
  GtkConfigStore config ;
  config.ConfigureDefaults ();
  config.ConfigureAttributes ();
  */

  // Run simulation
  std::cerr << "Simulating..."<<"\n";
  AnimationInterface anim;
  anim.SetOutputFile(animFile);
  if (netanim) anim.StartAnimation();
  setProgressTimer();
  Simulator::Stop(simStopTime);
  Simulator::Run();
  Simulator::Destroy();
  std::cerr << "All done!" << "\n";
  if (netanim) anim.StopAnimation();
  
  return 0;
}
