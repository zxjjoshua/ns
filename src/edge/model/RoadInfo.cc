#include "RoadInfo.h"

namespace ns3{
RoadInfo::RoadInfo(){

}

void RoadInfo::RoadInfoProceess(uint8_t* meessage){
    //区分是来自云端还是来自车辆
    //云端的包就直接存储并且广播
    //车辆端就直接进行道路信息获取，并且返回
}


//void RoadInfo::RoadInfoReply(DataBase* db, char* car_ip, int car_port);//used to serve customers, if the cars reequest for road info, the send back.

//Road* RoadInfo::RoadInfoParse(char* message);
//bool RoadInfo::RoadInfoSave(DataBase *db, car_info* car);
//void RoadInfo::RoadInfoBroadcast();// use broadcast tech to broad the meessage
}
