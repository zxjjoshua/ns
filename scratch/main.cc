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


// Network topology
//
//
//       10.1.1.0
// n0 -------------- n1   n2   n3   n4
//    point-to-point  |    |    |    |
//                    ================
//                      LAN 10.1.2.0
//
// - UDP flows from n0 to n1 and back
// - DropTail queues
// - Tracing of queues and packet receptions to file "udp-echo.tr"

#include <fstream>
#include <iostream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include <time.h>
//#include <hiredis/hiredis.h>
//#include "ns3/DataBase.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("UdpEchoExample");


void SetCarInfo(char* str, short int car_id, short int speed, float p_x,
  float p_y)
  {
    int len=0;
    char MT_BT=128+1;
    int ML=12;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&car_id,2);
    len+=2;
    memcpy(&str[len],&speed,2);
    len+=2;
    memcpy(&str[len],&p_x,4);
    len+=4;
    memcpy(&str[len],&p_y,4);
    len+=4;
}

void SetRoadInfo(char* str, uint8_t road_id, float a_x,
  float a_y, float b_x, float b_y, bool avalable)
  {
    int len=0;
    char MT_BT=128+2;
    int ML=17;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&road_id,1);
    len+=1;
    memcpy(&str[len],&a_x,4);
    len+=4;
    memcpy(&str[len],&a_y,4);
    len+=4;
    memcpy(&str[len],&b_x,4);
    len+=4;
    memcpy(&str[len],&b_y,4);
    len+=4;
    memcpy(&str[len],&avalable,1);
    len+=1;
}


void SetValidateInfo(char* str, short int car_id, short int point)
  {
    int len=0;
    char MT_BT=128+4;
    int ML=4;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&car_id,2);
    len+=2;
    memcpy(&str[len],&point,2);
    len+=2;
}

void SetDocumentInfo(char* str, short int car_id, time_t start_time, time_t end_time, time_t serve_time, short int serve_num,short* car_id_list)
  {
    int len=0;
    char MT_BT=128+3;
    int ML=2+8+8+8+2+serve_num;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&car_id,2);
    len+=2;
    memcpy(&str[len],&start_time,8);
    len+=8;
    memcpy(&str[len],&end_time,8);
    len+=8;
    memcpy(&str[len],&serve_time,8);
    len+=8;
    memcpy(&str[len],&serve_num,2);
    len+=2;
    for(int i=0;i<serve_num;i++){
      memcpy(&str[len],&(car_id_list[i]),2);
      len+=2;
    }
}

void SetDocSuccInfo(char* str, bool succ, uint8_t* ip)
  {
    int len=0;
    char MT_BT=128+12;
    int ML=5;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&succ,1);
    len+=1;
    for(int i=0;i<4;i++){
      memcpy(&str[len],&ip[i],1);
      len+=1;
    }
}

void SetValidateSuccInfo(char* str, bool succ, uint8_t* ip)
  {
    int len=0;
    char MT_BT=128+12;
    int ML=5;
    // char car_id=33;
    // short int speed=99;
    // float position_x=233.234;
    // float position_y=32.2216;
    memcpy(&str[len],&MT_BT,1);
    len++;
    memcpy(&str[len],&ML,4);
    len+=4;
    memcpy(&str[len],&succ,1);
    len+=1;
    for(int i=0;i<4;i++){
      memcpy(&str[len],&ip[i],1);
      len+=1;
    }
}


int
main (int argc, char *argv[])
{
//
// Users may find it convenient to turn on explicit debugging
// for selected modules; the below lines suggest how to do this
//
#if 1
  LogComponentEnable ("UdpEchoExample", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_ALL);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_ALL);
#endif
//
// Allow the user to override any of the defaults and the above Bind() at
// run-time, via command-line arguments
//

//  redisContext* c = redisConnect("127.0.0.1", 6379);
  bool useV6 = false;
  Address serverAddress_1;
  Address serverAddress_2;
  Address cloudAddress;

  CommandLine cmd;
  cmd.AddValue ("useIpv6", "Use Ipv6", useV6);
  cmd.Parse (argc, argv);
  uint32_t nCsma = 4;
//
// Explicitly create the nodes required by the topology (shown above).
//

  nCsma == 0 ? 1 : nCsma;
  NodeContainer p2pNodes;
  p2pNodes.Create(2);

  NodeContainer csmaNodes;
  csmaNodes.Add(p2pNodes.Get(0));
  csmaNodes.Create(nCsma);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

//CSMA配置
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  csma.SetDeviceAttribute ("Mtu", UintegerValue (1400));

  NetDeviceContainer csmaDevices = csma.Install (csmaNodes);
//

//互联网协议安装
  InternetStackHelper stack;
  stack.Install (p2pNodes.Get(1));
  stack.Install (csmaNodes);


  NS_LOG_INFO ("Create channels.");
//
// Explicitly create the channels required by the topology (shown above).
//


//
// We've got the "hardware" in place.  Now we need to add IP addresses.
//
  // NS_LOG_INFO ("Assign IP Addresses.");
  // if (useV6 == false)
  //   {
  //     Ipv4AddressHelper ipv4;
  //     ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  //     Ipv4InterfaceContainer i = ipv4.Assign (d);
  //     serverAddress = Address(i.GetAddress (1));
  //   }
  // else
  //   {
  //     Ipv6AddressHelper ipv6;
  //     ipv6.SetBase ("2001:0000:f00d:cafe::", Ipv6Prefix (64));
  //     Ipv6InterfaceContainer i6 = ipv6.Assign (d);
  //     serverAddress = Address(i6.GetAddress (1,1));
  //   }

  //ip地址配置
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces;
  p2pInterfaces = address.Assign (p2pDevices);
  serverAddress_1 = Address(p2pInterfaces.GetAddress (0));
  cloudAddress = Address(p2pInterfaces.GetAddress(1));
  // std::cout << "cloud address is "<< InetSocketAddress::ConvertFrom (from).GetIpv4 () <<std::endl;
  NS_LOG_INFO("cloud address is "<< int(cloudAddress.m_type)<<" and len is "<<int(cloudAddress.m_len)<<" and real length is "<<std::strlen((char*)cloudAddress.m_data));
  NS_LOG_INFO("server address is "<< int(serverAddress_1.m_type)<<" and len is "<<int(serverAddress_1.m_len));

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer csmaInterfaces;
  csmaInterfaces = address.Assign (csmaDevices);
  serverAddress_2 = Address(csmaInterfaces.GetAddress (0));
  // std::cout<<"the type is "<<int(serverAddress_1.m_type)<<" and its len !!"<<int(serverAddress_1.m_len)<<std::endl;
  // std::cout<<"the type is "<<int(serverAddress_2.m_type)<<" and its len !!"<<int(serverAddress_2.m_len)<<std::endl;
//////////////////////////////////////////////////////
//create multiple meessages to send
char str1[100];
char str2[100];
char str3[100];
char str4[100];


 SetCarInfo(str1, 1, 30, 23.23, 43.232);
 SetCarInfo(str2, 2, 40, 233.23, 3.232);
 SetCarInfo(str3, 3, 40, 43.2, 34.232);
 SetCarInfo(str4, 4, 30, 11.53, 23.232);

//SetRoadInfo(str1, 1, 1.23, 3.34, 2.34, 5.34, true);
//SetRoadInfo(str2, 2, 32.32, 33.22, 4.34, 45.6, true);
//SetRoadInfo(str3, 3, 23.1, 23.44, 13.234, 443.2, true);
//SetRoadInfo(str4, 4, 32.4, 45.65,4.44, 423.4, true);










//////////////////////////////////////////////////////

  NS_LOG_INFO ("Create Applications.");
//Edge
// Create a UdpEchoServer application on node one.
//
  uint16_t port = 9;  // well-known echo port number
  UdpEchoServerHelper server ( port);
  ApplicationContainer serverapps = server.Install (p2pNodes.Get (0));
  server.SetCloudServer(serverapps.Get(0), cloudAddress);
  serverapps.Start (Seconds (1.0));
  serverapps.Stop (Seconds (10.0));

  // serverapps = server.Install (csmaNodes.Get (0));
  // serverapps.Start (Seconds (1.0));
  // serverapps.Stop (Seconds (10.0));


//////////////////////////////////////////////////////
//cloud
  UdpEchoClientHelper cloud_server (serverAddress_1, port);
  // UdpEchoServerHelper cloud_server (port);
  serverapps= cloud_server.Install(p2pNodes.Get(1));
  cloud_server.SetCloud(serverapps.Get(0));
  cloud_server.SetAttribute ("MaxPackets", UintegerValue (0));
  cloud_server.SetAttribute ("Interval", TimeValue (Seconds (10)));
  cloud_server.SetAttribute ("PacketSize", UintegerValue (1));
  cloud_server.SetName(serverapps.Get(0),"cloud");

  serverapps.Start(Seconds(2));
  serverapps.Stop(Seconds(10.0));



//
// Create a UdpEchoClient application to send UDP datagrams from node zero to
// node one.
//
  uint32_t packetSize = 1024;
  uint32_t maxPacketCount = 1000;
  Time interPacketInterval = Seconds (0.5);
  UdpEchoClientHelper client (serverAddress_1, port);
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client.SetAttribute ("PacketSize", UintegerValue (packetSize));
  Packet::EnablePrinting();


  ApplicationContainer clientApps = client.Install (csmaNodes.Get(1));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));
  client.SetFill (clientApps.Get (0), str1);
  client.SetName(clientApps.Get(0),"n1");

//////////////////////////////////////////////////
  //uint32_t packetSize = 1024;
  //uint32_t maxPacketCount = 6;
  //Time interPacketInterval = Seconds (0.5);
  UdpEchoClientHelper client2 (serverAddress_1, port);
  client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client2.SetAttribute ("PacketSize", UintegerValue (packetSize));
  Packet::EnablePrinting();

  clientApps = client2.Install (csmaNodes.Get (2));
  clientApps.Start (Seconds (2.20));
  clientApps.Stop (Seconds (10.0));
  client2.SetFill (clientApps.Get (0), str2);
  client2.SetName(clientApps.Get(0),"n2");

///////////////////////////////////////////////////

  UdpEchoClientHelper client3 (serverAddress_1, port);
  client3.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client3.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client3.SetAttribute ("PacketSize", UintegerValue (packetSize));
  Packet::EnablePrinting();

  clientApps = client3.Install (csmaNodes.Get (3));
  clientApps.Start (Seconds (2.50));
  clientApps.Stop (Seconds (10.0));
  client3.SetFill (clientApps.Get (0), str3);
  client3.SetName(clientApps.Get(0),"n3");

//////////////////////////////////////////////////
//#if 0
//
// Users may find it convenient to initialize echo packets with actual data;
// the below lines suggest how to do this
//
  //client.SetFill (apps.Get (0), "fiveee");
//client.SetFill (apps.Get (1), "i'm n0");

//client.SetFill (apps.Get (1), "i'm n2");
//  client.SetFill (apps.Get (0), 0xa5, 1024);

  //uint8_t fill[] = { 0, 1, 2, 3, 4, 5, 6};
  //client.SetFill (apps.Get (0), fill, sizeof(fill), 1024);
//#endif

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  AsciiTraceHelper ascii;
  csma.EnableAsciiAll (ascii.CreateFileStream ("udp-echo.tr"));
  pointToPoint.EnablePcapAll ("second");
  csma.EnablePcap ("second", csmaDevices.Get (1), true);

//
// Now, do the actual simulation.
//

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
  return 0;
}
