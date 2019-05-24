#ifndef __carinfo__
#define __carinfo__
#include <iostream>
#include "DataBase.h"


#define table_name "carinfo_"
#define key_ttl 50
#define cloud_ip "12.3.2.21"
#define cloud_port 3232

typedef struct car_info{
    char car_id;
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
    static void CarInfoProcess(DataBase *db, char* ip, int from_port, char* message);

//    void set_key();
private:
    static car_info* CarInfoParse(char* message);
    static bool CarInfoSave(DataBase *db, car_info* car);
    static bool CarInfoUpload(char* car_id, DataBase *db);
    static car_info* CarInfoGet(char* car_id, DataBase);


};




#endif

