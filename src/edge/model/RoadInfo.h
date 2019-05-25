#ifndef __roadinfo__
#define __roadinfo__
#include "DataBase.h"
#include "CarInfo.h"

//there can be two type of message, first can be cloud-reply, second can be car-request
//需要先区分两种包


typedef struct Road{
    uint8_t* road_name;//or consider for a road_id?
    unsigned short int traffic_level;//a evaluating value, range from 0 to 5
    bool available;//wether the road is available for traffic
}Road;


class RoadInfo{
public:
    RoadInfo();
    static void RoadInfoProceess(uint8_t* meessage);
    static void RoadInfoReply(uint8_t* car_ip, int car_port);//used to serve customers, if the cars reequest for road info, the send back.
private:
    static Road* RoadInfoParse(uint8_t* message);
    static bool RoadInfoSave(car_info* car);
    static void RoadInfoBroadcast();// use broadcast tech to broad the meessage
};



#endif
