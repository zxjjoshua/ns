#include "RoadInfo.h"
#define cloud_ip "10.1.1.2"
namespace ns3{
RoadInfo::RoadInfo(){

}

void RoadInfo::RoadInfoProceess(uint8_t* message, Ptr<Socket> socket){
    //区分是来自云端还是来自车辆
    //云端的包就直接存储并且广播
    //车辆端就直接进行道路信息获取，并且返回
    Road* road=RoadInfoParse(message);
    //std::cout <<"here here!!"<<std::endl;
    RoadInfoSave(road);
    RoadInfoUpload(message, socket);
}

bool RoadInfo::RoadInfoSave(Road* car){
  return true;
}

void RoadInfo::RoadInfoUpload(uint8_t* message, Ptr<Socket> socket){
  int len=std::strlen((char*)message);
  Ptr<Packet> packet=Create<Packet> (message, len+1);
  uint8_t ip[]=cloud_ip;
  Address cloud(3,ip, std::strlen((char*)ip));
  // printf("!!!!!!!!get address %s",to.m_data);
  // cloud.m_data=;
  std::cout <<"here here!!"<<std::endl;
  socket->SendTo(packet, 0, cloud);
}


Road* RoadInfo::RoadInfoParse(uint8_t* message){
  Road* road=new Road;
  int len=0;
  char MT_BT;
  int ML;
  float point;

  memcpy(&MT_BT, &message[len++], 1);
  memcpy(&ML, &message[len], 4);
  len+=4;


  memcpy(&road->road_name,&message[len],1);
  len+=1;
  memcpy(&point,&message[len],4);
  len+=4;
  memcpy(&point,&message[len],4);
  len+=4;
  memcpy(&point,&message[len],4);
  len+=4;
  memcpy(&point,&message[len],4);
  len+=4;
  memcpy(&road->available,&message[len],1);
  len+=1;
  return road;
}


//void RoadInfo::RoadInfoReply(DataBase* db, char* car_ip, int car_port);//used to serve customers, if the cars reequest for road info, the send back.

//Road* RoadInfo::RoadInfoParse(char* message);
//bool RoadInfo::RoadInfoSave(DataBase *db, car_info* car);
//void RoadInfo::RoadInfoBroadcast();// use broadcast tech to broad the meessage
}
