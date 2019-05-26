#ifndef __roadinfo__
#define __roadinfo__
#include "DataBase.h"
#include "CarInfo.h"
#include "ns3/ipv4-address.h"

//there can be two type of message, first can be cloud-reply, second can be car-request
//需要先区分两种包
namespace ns3{

typedef struct Road{
    uint8_t* road_name;//or consider for a road_id?
    unsigned short int traffic_level;//a evaluating value, range from 0 to 5
    bool available;//wether the road is available for traffic
}Road;


class RoadInfo{
public:
    RoadInfo();
    static void RoadInfoProceess(uint8_t* meessage, Ptr<Socket> socket);
    static void RoadInfoReply(uint8_t* car_ip, int car_port);//used to serve customers, if the cars reequest for road info, the send back.
    static void RoadAlert(Address from, uint8_t* message, Ptr<Socket> socket);
    static void AlertParset(uint8_t* message);  
private:
    static Road* RoadInfoParse(uint8_t* message);
    static bool RoadInfoSave(Road* car);
    static void RoadInfoBroadcast();// use broadcast tech to broad the meessage
    static void RoadInfoUpload(uint8_t* message, Ptr<Socket> socket);
};

}

#endif
