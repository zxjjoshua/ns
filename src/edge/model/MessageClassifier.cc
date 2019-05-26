#include "MessageClassifier.h"
#include <string.h>
#include "CarInfo.h"
#include "RoadInfo.h"
#include "Encourage.h"
// #include "ns3/internet-module.h"
// #include "ns3/point-to-point-module.h"
// #include <fstream>
#define MODULE "MessageClassifier"

namespace ns3{



void MessageClassifier::Router(uint8_t* message, Address from, Ptr<Socket> socket){
    //classify via classify table:
    //carinfo
    //roadinfo
    //encourage
    //entertainment
    //message format:
    //MT1bit BT1bit
    char MT;


    // NodeContainer p2pNodes;
    // p2pNodes.Create(5);
    // NetDeviceContainer p2pDevices;
    // PointToPointHelper pointToPoint;
    // pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    // pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
    // p2pDevices = pointToPoint.Install (p2pNodes);
    // Ipv4AddressHelper address;
    // address.SetBase ("10.1.1.0", "255.255.255.0");
    // Ipv4InterfaceContainer p2pInterfaces;
    // p2pInterfaces = address.Assign (p2pDevices);
    uint8_t ip[]="10.1.1.2";
    Address to(3,ip, std::strlen((char*)ip));
    printf("!!!!!!!!get address %s",to.m_data);


    // to.m_data=;
    memcpy( &MT, message, 1);
    std::cout<<"this is MT "<<(int)(MT)<<std::endl;
    if(int(MT)<0){
        int BT=int(message[0]&0x7f);//第一位归零
        std::cout<<"this is BT "<<BT<<std::endl;
        switch (BT) {
        case 1://车辆信息 1
            CarInfo::CarInfoProcess(message, socket);
            break;
        case 2://基础设施上传道路信息 2
            RoadInfo::RoadInfoProceess(message, socket);
		break;
        case 3://激励记录信息上传 3
            Encourage::EncourageDocument(from,message, socket);
		break;
        case 4://激励验证信息上传 4
            Encourage::EncourageValidate(from, message, socket);
		break;
            //车辆的道路请求信息 6

            //车载娱乐 7
            //云端道路信息表同步 8
            //道路拥堵警报 11
        case 12://激励记录成功返回信息 12
            Encourage::EncourageDocmentSucc(from, message, socket);
		break;

        case 13://激励验证成功返回信息 13
            Encourage::EncourageValidateSucc(from, message, socket);
		break;

        default:
            break;
        }

    }
    else{
      std::string reply="not ok";
      Ptr<Packet> packet=Create<Packet>((uint8_t*)(reply.c_str()),reply.length());
      socket->SendTo(packet, 0, to);
        //Communication::Send_To(message,ip,port);
    }
}

std::vector<std::string> MessageClassifier::ip2int(char *ip)
{
    //const char* convert to char*
    char * strc = new char[strlen(ip)+1];
    strcpy(strc, ip);
    std::vector<std::string> resultVec;
    char* tmpStr = strtok(strc,".");
    while (tmpStr != NULL)
    {
        resultVec.push_back(std::string(tmpStr));
        tmpStr = strtok(NULL, ".");
    }
    delete[] strc;

    return resultVec;
}

}
