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

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FatTree");

std::map<int, Ipv4Address> nodeAddresses;


Ipv4InterfaceContainer connectNodes (Ptr<Node> node1, Ptr<Node> node2, char* linkRate, char* linkDelay, Ipv4AddressHelper addressHelper) 
{
  NodeContainer nodePair;
  nodePair.Add(node1);
  nodePair.Add(node2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue (linkRate));
  pointToPoint.SetChannelAttribute ("Delay", StringValue (linkDelay));
  pointToPoint.SetQueue("ns3::DropTailQueue");

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

void sendData(Ptr<Node> srcNode, Ptr<Node> dstNode, uint16_t port, uint64_t data, Time startTime, Time stopTime)
{
  NodeContainer nodePair;
  nodePair.Add(srcNode);
  nodePair.Add(dstNode);

  Ptr<FtpServer> ftpServer = CreateObject<FtpServer>();
  ftpServer->Configure(data, port, startTime, true);
  dstNode->AddApplication(ftpServer);
  ftpServer->SetStartTime(startTime - Seconds(0.001));
  ftpServer->SetStopTime(stopTime);
  
  Address ftpServerAddress(InetSocketAddress(nodeAddresses[dstNode->GetId()], port));

  Ptr<FtpClient> ftpClient = CreateObject<FtpClient>();
  ftpClient->Configure(ftpServerAddress, data);
  srcNode->AddApplication(ftpClient);
  ftpClient->SetStartTime(startTime);
}


int main (int argc, char *argv[])
{
  // Fundamental parameters
  int serverCount_total = 64;
  int portCount_perSwitch = 8;

  char* linkRate = (char*)"10Gbps";
  char* linkDelay = (char*)"5us";

  int bgFlowByteCount = 10000000;
  //int smFlowByteCount = 50000;
  //int qFlowByteCount = 2000;
  //int qFlowPartCount = 25;

  // Derived parameters
  int podCount_total = serverCount_total / (portCount_perSwitch * portCount_perSwitch) * 4;
  int serverCount_perPod = serverCount_total / podCount_total;
  int serverCount_perTorSwitch = portCount_perSwitch / 2;
  int torSwitchCount_perPod = serverCount_perPod / portCount_perSwitch * 2;
  int aggSwitchCount_perPod = torSwitchCount_perPod;
  int torSwitchCount_total = podCount_total * torSwitchCount_perPod;
  int aggSwitchCount_total = torSwitchCount_total;
  int coreSwitchCount_total = aggSwitchCount_total / 2;
  int switchCount_total = torSwitchCount_total + aggSwitchCount_total + coreSwitchCount_total;
  
  //int nodeCount_total = serverCount_total + switchCount_total;
  
  std::cout << "Servers  = " << serverCount_total << "\n";
  std::cout << "Pods     = " << podCount_total << "\n";
  std::cout << "Switches = " << torSwitchCount_total << " + " << aggSwitchCount_total << " + " << coreSwitchCount_total << " = " << switchCount_total << "\n"; 

  // Other parameters
  std::string animFile("fat-tree.tr");  // Name of file for animation output  


  // Initial Configurations

bool set_successful = true;

 set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::SegmentSize",UintegerValue(1460));
 set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::InitialCwnd",UintegerValue(2));
 set_successful &= Config::SetDefaultFailSafe("ns3::TcpSocket::DelAckCount",UintegerValue(1));
 set_successful &= Config::SetDefaultFailSafe("ns3::TcpL4Protocol::SocketType",StringValue("ns3::TcpNewReno"));
 set_successful &= Config::SetDefaultFailSafe("ns3::RttEstimator::MinRTO",TimeValue(Seconds(0.01)));
 set_successful &= Config::SetDefaultFailSafe("ns3::Ipv4GlobalRouting::RandomEcmpRouting", BooleanValue(true));
 
 if (!set_successful) {
   std::cout << "Error: Could not set defaults" << std::endl;
   return 0;
 }

  // Generating the nodes
  NodeContainer servers;
  NodeContainer torSwitches;
  NodeContainer aggSwitches;
  NodeContainer coreSwitches;

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
  std::cout << "Generating topology..."<<"\n";
  std::cout << "Connecting servers to ToR switches..."<<"\n";
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
  std::cout << "Connecting ToR switches to aggregate switches..."<<"\n";
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
  std::cout << "Connecting aggregate switches to core switches..."<<"\n";
  for (coreSwitchID = 0; coreSwitchID < coreSwitchCount_total; coreSwitchID++)
  {
    Ipv4AddressHelper coreAddressHelper;
    char *coreBaseAddress = (char *) malloc(sizeof (char) * 20);
    sprintf(coreBaseAddress,"30.%d.0.0", coreSwitchID); 
    coreAddressHelper.SetBase (coreBaseAddress, "255.255.255.0");
    for (aggSwitchID = coreSwitchID; aggSwitchID < aggSwitchCount_total; aggSwitchID+=aggSwitchCount_perPod)
    {
      connectNodes(coreSwitches.Get(coreSwitchID), aggSwitches.Get(aggSwitchID),  linkRate, linkDelay, coreAddressHelper);
      coreAddressHelper.NewNetwork();  
    }
  }
  
  // Setup routing table with ECMP
  std::cout << "Setting up routing tables..."<<"\n";
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  // Setup node locations for animation
  std::cout << "Setting up locations for animation..." << "\n";  
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
  std::cout << "Setting up traffic..." << "\n";
  //sendData(servers.Get(0), servers.Get(10), 5555, 10000000, Seconds(0.1), Seconds(1.0));
  //sendData(servers.Get(20), servers.Get(50), 5555, 10000000, Seconds(0.1), Seconds(1.0));
  
  std::cout << "Setting up long background flows..." << "\n";
  UniformVariable bgRnd;   
  UniformVariable startTimeRnd;
  for (serverID = 0; serverID < serverCount_total/30; serverID++) 
  {
    int otherServerID;
    while ((otherServerID = bgRnd.GetInteger(0, serverCount_total)) == serverID);
    sendData(servers.Get(serverID), servers.Get(otherServerID), 5555 + serverID, bgFlowByteCount, Seconds(0.1) + MilliSeconds(startTimeRnd.GetValue(-1,1)), Seconds(1.0)); 
  }

  std::cout << "Setting up short message flows..." << "\n";



  std::cout << "Setting up parition/aggregate query flows..." << "\n";
  


  /*
  GtkConfigStore config;
  config.ConfigureDefaults ();
  config.ConfigureAttributes ();
  */

  // Run simulation
  std::cout << "Simulating..."<<"\n";
  AnimationInterface anim;
  anim.SetOutputFile(animFile);
  anim.StartAnimation();
  Simulator::Stop(Seconds(2.0));
  Simulator::Run();
  Simulator::Destroy();
  std::cout << "All done!" << "\n";
  anim.StopAnimation();
  
  return 0;
}
