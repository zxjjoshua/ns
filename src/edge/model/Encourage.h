#ifndef __encourage__
#define __encourage__
#include "DataBase.h"
#define cloud_ip "12.3.2.21"
#define cloud_port 3232
#include "ns3/ipv4-address.h"

namespace ns3 {
class MessageClassifier;
class Encourage
{
public:
    Encourage();
    static void EncourageDocument(Address ip, uint8_t* message);
    static void EncourageValidate(Address ip, uint8_t* message);
    static void EncourageDocmentSucc(Address ip, uint8_t* message);
    static void EncourageValidateSucc(Address* ip, uint8_t* message);

    static void AddIp(uint8_t* message, uint8_t *ip, char* send_buff, int *len);
    static void AddPort(uint8_t* message, short port, char* send_buff, int *len);
};
}
#endif
