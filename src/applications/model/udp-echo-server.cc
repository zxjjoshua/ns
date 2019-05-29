/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2007 University of Washington
 *
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

#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/socket.h"
#include "ns3/udp-socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/MessageClassifier.h"
#include "udp-echo-server.h"
#include <pthread.h>

#define NUM_THREADS 10

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("UdpEchoServerApplication");

NS_OBJECT_ENSURE_REGISTERED (UdpEchoServer);

TypeId
UdpEchoServer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::UdpEchoServer")
    .SetParent<Application> ()
    .SetGroupName("Applications")
    .AddConstructor<UdpEchoServer> ()
    .AddAttribute ("Port", "Port on which we listen for incoming packets.",
                   UintegerValue (9),
                   MakeUintegerAccessor (&UdpEchoServer::m_port),
                   MakeUintegerChecker<uint16_t> ())
    .AddTraceSource ("Rx", "A packet has been received",
                     MakeTraceSourceAccessor (&UdpEchoServer::m_rxTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("RxWithAddresses", "A packet has been received",
                     MakeTraceSourceAccessor (&UdpEchoServer::m_rxTraceWithAddresses),
                     "ns3::Packet::TwoAddressTracedCallback")
  ;
  return tid;
}

UdpEchoServer::UdpEchoServer ()
{
  NS_LOG_FUNCTION (this);
  is_could=false;
  // for(int i=0;i<MaxConnect;i++){
  //   m_stack.push(i);
  // }

}

UdpEchoServer::~UdpEchoServer()
{
  NS_LOG_FUNCTION (this);
  m_socket = 0;
  m_socket6 = 0;
}

void
UdpEchoServer::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  Application::DoDispose ();
}

void
UdpEchoServer::StartApplication (void)
{
  NS_LOG_FUNCTION (this);

  if (m_socket == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      m_socket = Socket::CreateSocket (GetNode (), tid);
      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), m_port);
      if (m_socket->Bind (local) == -1)
        {
          NS_FATAL_ERROR ("Failed to bind socket");
        }
      if (addressUtils::IsMulticast (m_local))
        {
          Ptr<UdpSocket> udpSocket = DynamicCast<UdpSocket> (m_socket);
          if (udpSocket)
            {
              // equivalent to setsockopt (MCAST_JOIN_GROUP)
              udpSocket->MulticastJoinGroup (0, m_local);
            }
          else
            {
              NS_FATAL_ERROR ("Error: Failed to join multicast group");
            }
        }
    }

  if (m_socket6 == 0)
    {
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      m_socket6 = Socket::CreateSocket (GetNode (), tid);
      Inet6SocketAddress local6 = Inet6SocketAddress (Ipv6Address::GetAny (), m_port);
      if (m_socket6->Bind (local6) == -1)
        {
          NS_FATAL_ERROR ("Failed to bind socket");
        }
      if (addressUtils::IsMulticast (local6))
        {
          Ptr<UdpSocket> udpSocket = DynamicCast<UdpSocket> (m_socket6);
          if (udpSocket)
            {
              // equivalent to setsockopt (MCAST_JOIN_GROUP)
              udpSocket->MulticastJoinGroup (0, local6);
            }
          else
            {
              NS_FATAL_ERROR ("Error: Failed to join multicast group");
            }
        }
    }

  m_socket->SetRecvCallback (MakeCallback (&UdpEchoServer::HandleRead, this));
  m_socket6->SetRecvCallback (MakeCallback (&UdpEchoServer::HandleRead, this));
}

void
UdpEchoServer::StopApplication ()
{
  NS_LOG_FUNCTION (this);

  if (m_socket != 0)
    {
      m_socket->Close ();
      m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
    }
  if (m_socket6 != 0)
    {
      m_socket6->Close ();
      m_socket6->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
    }
}

void
UdpEchoServer::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;
  Address from;
  Address localAddress;
  // Ptr<Socket> socket=0;

  pthread_t tids[NUM_THREADS];
  int i=0;
  while ((packet = socket->RecvFrom (from)))
    {
      socket->GetSockName (localAddress);
      m_rxTrace (packet);
      m_rxTraceWithAddresses (packet, from, localAddress);
	 // std::cout <<"in the while head"<<std::endl;
      if (InetSocketAddress::IsMatchingType (from))
        {
          NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds () << "s server received " << packet->GetSize () << " bytes from " <<
                       InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " <<
                       InetSocketAddress::ConvertFrom (from).GetPort ());
    //NS_LOG_INFO("server reecieveed "<<packet->ToString());
    //packet->Output(packet->GetSize());
        uint8_t* content= packet->GetContent(packet->GetSize());
        // NS_LOG_INFO("this is what seerver get" <<content);
	       if(is_could){
           std::cout <<"this is cloud server"<<std::endl;
         }
         else{
           // int i=m_stack.(pop);
           // int ret = pthread_create(&m_threads[i], NULL, MessageClassifier::Router,(void)(*)&content, (void)(*)&from, (void)(*)&ocket);
          //  if (ret != 0)
          // {
          //    std::cout << "pthread_create error: error_code=" << ret << std::endl;
          //    m_stack.push(i);
          // }
           MessageClassifier::Router(content, from, socket);
         }

        // if (socket == 0)
        //   {
        //     TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
        //     socket = Socket::CreateSocket (GetNode (), tid);
        //     InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), m_port);
        //     if (m_socket->Bind (local) == -1)
        //       {
        //         NS_FATAL_ERROR ("Failed to bind socket");
        //       }
        //   }
	// std::cout <<"in the if"<<std::endl;
      }
      else if (Inet6SocketAddress::IsMatchingType (from))
        {
          NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds () << "s server received " << packet->GetSize () << " bytes from " <<
                       Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " <<
                       Inet6SocketAddress::ConvertFrom (from).GetPort ());
        }
      //
      // packet->RemoveAllPacketTags ();
      // packet->RemoveAllByteTags ();

	// std::cout << "from info "<< int(from.m_type)<<" and length "<<int(from.m_len)<<" and real len is "<<std::strlen((char*)from.m_data)<<std::endl;
	// std::cout <<" ip is "<<int(from.m_data[0])<<"."<<int(from.m_data[1])<<"."<<int(from.m_data[2])<<"."<<int(from.m_data[3])<<"."<<int(from.m_data[4])<<"."<<int(from.m_data[7])<<std::endl;
       // NS_LOG_LOGIC ("Echoing packet");
  //     uint8_t ip[7];
	// ip[0]=10;
	// ip[1]=1;
	// ip[2]=2;
	// ip[3]=2;
	// ip[4]=192;
	// ip[5]=1;
	// ip[6]=2;
	// ip[7]=188;
	// from.m_data[0]=10;
	// from.m_data[1]=1;
	// from.m_data[2]=2;
	// from.m_data[3]=5;
	// //from.m_data[4]='\0';
	// //from.m_data[5]='\0';
	// //from.m_data[6]='\0';
	// uint8_t type=4;
	// uint8_t len=7;
	// Address cloud(type,ip, len);
  //     socket->SendTo (packet, 0, from);
	//memcpy(&from.m_data,&ip,8);
	//socket->SendTo (packet, 0, from);
      //
      // if (InetSocketAddress::IsMatchingType (from))
      //   {
      //     NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds () << "s server sent " << packet->GetSize () << " bytes to " <<
      //                  InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " <<
      //                  InetSocketAddress::ConvertFrom (from).GetPort ());
      //   }
      // else if (Inet6SocketAddress::IsMatchingType (from))
      //   {
      //     NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds () << "s server sent " << packet->GetSize () << " bytes to " <<
      //                  Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " <<
      //                  Inet6SocketAddress::ConvertFrom (from).GetPort ());
      //   }
    }
	// std::cout <<"the end"<<std::endl;
}

void UdpEchoServer::Send(Ptr<Packet> packet, Address to){
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> socket= Socket::CreateSocket (GetNode (), tid);
  socket->SendTo(packet, 0, to);
}

void UdpEchoServer::SetName(char* name){
  strcpy(name,this->m_name);
}

char* UdpEchoServer::GetName(void){
  return this->m_name;
}

void UdpEchoServer::SetCloud(bool k){
  is_could=k;
}

void UdpEchoServer::SetCloudServer(Address cloud){
  m_cloud=cloud;
}



} // Namespace ns3
