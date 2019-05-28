#ifndef __carinfo__
#define __carinfo__
#include <iostream>
#include "DataBase.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/packet.h"
#include "ns3/internet-module.h"

#define table_name "carinfo_"
#define key_ttl 50
#define cloud_ip "10.1.1.2"
#define cloud_port 3232

namespace ns3{
typedef struct car_info{
    short car_id;
    unsigned short int car_speed;
    float position_x;
    float position_y;

}car_info;


//CarInfo
//车辆信息处理模块
//
class CarInfo{
public:
    CarInfo();
    static void CarInfoProcess(Address from, uint8_t* message, Ptr<Socket> socket);

//    void set_key();
    static car_info* CarInfoParse(uint8_t* message);
    static bool CarInfoSave(car_info *car);
    static bool CarInfoUpload(Address from, car_info* car, Ptr<Socket> socket);
    static car_info* CarInfoGet(uint8_t *car_id);


};

}


#endif
