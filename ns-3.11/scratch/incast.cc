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
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

#include "FtpClient.h"
#include "FtpServer.h"

#include "ns3/point-to-point-net-device.h"
#include "ns3/loopback-net-device.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Incast");


/*
void
placeNode(Ptr<Node> curnode, int x, int y, int z) {
  Ptr<CanvasLocation> curnodeLoc = curnode->GetObject<CanvasLocation> ();
  if (curnodeLoc == 0) {
    curnodeLoc = CreateObject<CanvasLocation> ();
    curnode->AggregateObject(curnodeLoc);
  }
  Vector locVec (x, y, z);
  curnodeLoc->SetLocation(locVec);
}
*/

/*
void
printStats(NodeContainer nodes) {
  uint64_t ndroppedbytes = 0;
  uint64_t ntxetherbytes = 0;
  uint64_t ntxdelaybytes = 0;
  uint64_t maxqueuelen = 0;

  for(uint32_t i = 0; i < nodes.GetN(); i++) {
    Ptr<Node> curnode = nodes.Get(i);
    for(uint32_t d = 0; d < curnode->GetNDevices(); d++) {
 
      Ptr<NetDevice> curdev = curnode->GetDevice(d);
      NS_ASSERT(curdev);
      
      //If loopback, skip
      if (DynamicCast<LoopbackNetDevice> (curdev)) {
        continue;
      }

      Ptr<PointToPointNetDevice> ptpdev = curdev->GetObject<PointToPointNetDevice>();
      Ptr<Queue> queue = ptpdev->GetQueue();
      ndroppedbytes += queue->GetTotalDroppedBytes();

      Ptr<DropTailQueue> dtqueue = queue->GetObject<DropTailQueue>();
      ntxetherbytes += dtqueue->GetTotalEtherBytes();
      ntxdelaybytes += dtqueue->GetTotalDelayBytes();

      if(curnode->GetId() == 0) {
        //Get max value of queue
        if(queue->GetMaxPackets() > maxqueuelen) {
          maxqueuelen = queue->GetMaxPackets();
        }
      }
    }
  }

  std::cout << "************************" << std::endl;
  //number of dropped bytes, number of txed packet bytes, number of txed delay bytes, max queue length in packets
  std::cout << ndroppedbytes << "\t" << ntxetherbytes << "\t" << ntxdelaybytes << "\t" << maxqueuelen << std::endl; 
}
*/

int 
main (int argc, char *argv[])
{
  uint32_t nSources = 1;
  uint32_t runNum = 1;
  bool enableDelay = false;
  bool enableSACK = false;

  CommandLine cmd;
  cmd.AddValue("numSources" , "Number of incast sources", nSources);
  cmd.AddValue("enableDelay", "Enable delay messages", enableDelay);
  cmd.AddValue("enableSACK", "Enable TCP Selective Acknowledgements",enableSACK);
  cmd.AddValue("runNumber", "Specify Run Number", runNum);
  cmd.Parse(argc,argv);

  //Set Defaults
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true)); 
  
  bool set_successful = true;
  //set_successful &= Config::SetDefaultFailSafe("ns3::NscTcpL4Protocol::UseSendMoreCallback",BooleanValue(true));
  //set_successful &= Config::SetDefaultFailSafe("ns3::DropTailQueue::Mode",EnumValue(ns3::DropTailQueue::PACKETS));
  //set_successful &= Config::SetDefaultFailSafe("ns3::DropTailQueue::MaxPackets",UintegerValue(100));
  //set_successful &= Config::SetDefaultFailSafe("ns3::PointToPointNetDevice::Mtu",UintegerValue(1500));
  //set_successful &= Config::SetDefaultFailSafe("ns3::Ipv4L3Protocol::EnableDelay",BooleanValue(enableDelay));
  //set_successful &= Config::SetDefaultFailSafe("ns3::Ipv4L3Protocol::HighThreshold",UintegerValue(600));
  //set_successful &= Config::SetDefaultFailSafe("ns3::Ipv4L3Protocol::LowThreshold",UintegerValue(300));
 
  if (!set_successful) {
    std::cout << "Error: Could not set defaults" << std::endl;
    return 0;
  }

  //Set Random number generators
  srand(runNum);
  SeedManager::SetRun(runNum);

  uint32_t totaltx = 1*1024*1024;

  NodeContainer srcpair[nSources];
  NodeContainer bottlepair;

  bottlepair.Create(2);

  for(uint32_t i = 0; i < nSources; i++) {
    srcpair[i].Create(1);
    srcpair[i].Add(bottlepair.Get(0));
  }

  //Create Stacks
  InternetStackHelper stack;
  stack.Install(bottlepair.Get(0));

  InternetStackHelper linstack;
  linstack.SetTcp("ns3::NscTcpL4Protocol", "Library", StringValue("liblinux2.6.26.so"));
  for(uint32_t i = 0; i < nSources; i++) {
    linstack.Install(srcpair[i].Get(0));
  }
  linstack.Install(bottlepair.Get(1));

  //Set TCP properties
  Config::Set ("/NodeList/*/$ns3::Ns3NscStack<linux2.6.26>/net.ipv4.tcp_congestion_control", StringValue ("reno"));
  Config::Set ("/NodeList/*/$ns3::Ns3NscStack<linux2.6.26>/net.ipv4.tcp_timestamps",StringValue("0"));
  Config::Set ("/NodeList/*/$ns3::Ns3NscStack<linux2.6.26>/net.ipv4.tcp_no_metrics_save", StringValue ("1"));
  if(enableSACK) {
    Config::Set ("/NodeList/*/$ns3::Ns3NscStack<linux2.6.26>/net.ipv4.tcp_sack", StringValue ("1"));
  }
  else {
    Config::Set ("/NodeList/*/$ns3::Ns3NscStack<linux2.6.26>/net.ipv4.tcp_sack", StringValue ("0"));
  }

  //Create devices
  PointToPointHelper PointToPoint;
  PointToPoint.SetDeviceAttribute ("DataRate", StringValue ("1Gbps"));
  PointToPoint.SetChannelAttribute ("Delay", StringValue ("25us"));
  PointToPoint.SetQueue("ns3::DropTailQueue");

  NetDeviceContainer srcdev[nSources];
  for(uint32_t i = 0; i < nSources; i++) {
    srcdev[i] = PointToPoint.Install(srcpair[i]);
  }

  NetDeviceContainer bottledev;
  bottledev = PointToPoint.Install(bottlepair);

  //Set base IP address
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer srciface[nSources];
  for(uint32_t i = 0; i < nSources; i++) {
    srciface[i] = address.Assign(srcdev[i]);
    address.NewNetwork();
  }

  Ipv4InterfaceContainer bottleiface;
  bottleiface = address.Assign(bottledev);
    
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  UniformVariable jitter(0,0.001);
  //Create main application
  for(uint32_t i = 0; i < nSources; i++) {
    double curjitter = jitter.GetValue();

    Ptr<FtpServer> ftpserv = CreateObject<FtpServer> ();
    ftpserv->Configure(totaltx/nSources,5555+i,Seconds(1.+curjitter),true);
    bottlepair.Get(1)->AddApplication(ftpserv);
    ftpserv->SetStartTime(Seconds(0.5));
    ftpserv->SetStopTime(Seconds(20.));
    
    Address ftpservAddr (InetSocketAddress(bottleiface.GetAddress(1),5555+i));
    
    Ptr<FtpClient> ftpclient = CreateObject<FtpClient> ();
    ftpclient->Configure(ftpservAddr, totaltx/nSources);
    srcpair[i].Get(0)->AddApplication(ftpclient);
    ftpclient->SetStartTime(Seconds(1.+curjitter));
    ftpclient->SetStopTime(Seconds(20.));
  }

  /*
  for(uint32_t i = 0; i < nSources; i++) {
    placeNode(srcpair[i].Get(0), i*2, 2 ,0);
  }
  placeNode(bottlepair.Get(0), nSources, 4, 0);
  placeNode(bottlepair.Get(1), nSources, 6, 0);
  */

  //Setup animation params
  //AnimationInterface anim;
  //anim.SetOutputFile ("anim.txt");
  //anim.StartAnimation();

  //Enable pcap tracing
  PointToPoint.EnablePcap("incast",srcpair[0]);

  NodeContainer allnodes;
  for(uint32_t i = 0; i < nSources; i++) {
    allnodes.Add(srcpair[i].Get(0));
  }
  allnodes.Add(bottlepair);
  //Simulator::Schedule(Seconds(21),&printStats, allnodes);

  Simulator::Stop(Seconds(21.1));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
