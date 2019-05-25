#include "CarInfo.h"
#include <string.h>
#define EXPIRE_TIME 50

namespace ns3{
CarInfo::CarInfo(){


}



//将处理的车辆信息结果存在表内，并且设置expire time，过期自动销毁
//将处理的车辆信息发送到云端
//MTBT车辆id，车辆速度，加速度，车辆位置x，车辆位置y
//“unsigned int, ”
void CarInfo::CarInfoProcess(uint8_t* message, Ptr<Socket> socket){
    car_info* car;
    uint8_t* key;
    uint8_t* car_id;
    // std::cout << ip<<" and messagee is "<<message<< std::endl;
    car=CarInfoParse(message);
//    key=strcat(table_name,car_id);

    CarInfoSave(car);
    uint8_t* value;
//    car=CarInfoParse(message);
//    if(!CarInfoSave(db,car)){
//        std::cout<<"car info save failed"<<std::endl;
//    }
//    db->SetKey(key,value);
//    db->ExpireKey(key,EXPIRE_TIME);

    CarInfoUpload(car, socket);
    free(car);

}


car_info* CarInfo::CarInfoParse(uint8_t* message){
    car_info* car=new car_info;//一定要先申明空间
    int len=0;
    char carid;
    char MT_BT;
    int ML;

    memcpy(&MT_BT, &message[len++], 1);
    memcpy(&ML, &message[len], 4);
    std::cout << int(MT_BT)<<" and messagee is "<<ML<< std::endl;
    len+=4;

    car->car_id=message[len++];
//    memcpy(&(car->car_id), &message[len++], 1);
//    car->car_id=int(carid);

//    memcpy(&car->car_speed, &message[len], 2);
    car->car_speed=message[len];
    len+=2;

    memcpy(&car->position_x, &message[len], 4);
//    car->position_x=message[len];
    len+=4;
    memcpy(&car->position_y, &message[len], 4);
//    car->position_y=message[len];
    len+=4;
    std::cout <<" and messagee is "<<car->position_x<< std::endl;
    printf("%f\n",car->position_x);

    return car;
}


//存储车辆数据，注意考虑信息之间用逗号分隔
bool CarInfo::CarInfoSave(car_info *car){
    // char key[]="";
    int len = 0;
    uint8_t value[100];
    uint8_t carid[3];
    int message_len=11;

    // sprintf(carid, "%d",car->car_id);

    memcpy(&value[len],&(car->car_id),1);
    len++;
//    std::cout<<"in heere"<<carid << std::endl;

    memcpy(&value[len],&message_len,4);
    len+=4;


//    memcpy(&a[len],&c,strlen(c));
//    len+=strlen(c);
    memcpy(&value[len],&car->car_id,1);
    len+=1;

    memcpy(&value[len],&car->car_speed,2);
    len+=2;
    memcpy(&value[len],&car->position_x,4);
    len+=4;
    memcpy(&value[len],&car->position_y,4);
    len+=4;

    // strcat(key,table_name);
    // strcat(key,carid);
//    std::cout <<"this is car info "<<key<<std::endl;





   //  if(!(db->SetKey(key,value)))
   //  {
   //      return false;
   //  }
   //
   // if(!(db->ExpireKey(key,EXPIRE_TIME))){
   //      return false;
   //  }

   return true;

}

car_info* CarInfo::CarInfoGet(uint8_t *car_id)
{
    car_info* car=NULL;
    return car;
}


//通过定义的云端ip，端口，直接从数据库将包取出，发送到云端
bool CarInfo::CarInfoUpload(car_info* car, Ptr<Socket> socket){
  int len = 0;
  uint8_t value[100];
  uint8_t carid[3];
  int message_len=11;

  // sprintf(carid, "%d",car->car_id);

  memcpy(&value[len],&(car->car_id),1);
  len++;
//    std::cout<<"in heere"<<carid << std::endl;

  memcpy(&value[len],&message_len,4);
  len+=4;


//    memcpy(&a[len],&c,strlen(c));
//    len+=strlen(c);
  memcpy(&value[len],&car->car_id,1);
  len+=1;

  memcpy(&value[len],&car->car_speed,2);
  len+=2;
  memcpy(&value[len],&car->position_x,4);
  len+=4;
  memcpy(&value[len],&car->position_y,4);
  len+=4;

  Ptr<Packet> packet=Create<Packet> (value, len+1);
  uint8_t ip[]="10.1.1.2";
  Address cloud(3,ip, 4));
  // printf("!!!!!!!!get address %s",to.m_data);
  // cloud.m_data=;
  socket->SendTo(packet, 0, cloud);

  //send
  return true;
    //上传到云端的消息应该附带车辆ip吗？
    //while(!Communication::Send_To(db->GetKey(key),cloud_ip, cloud_port)){
      //  std::cout << "info send failed"<<std::endl;
    //}

}
}
