#ifndef __encourage__
#define __encourage__
#include "DataBase.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/packet.h"

namespace ns3 {
class MessageClassifier;
class Encourage
{
public:
    Encourage();
    static void EncourageDocument(Address ip, uint8_t* message, Ptr<Socket> socket);
    static void EncourageValidate(Address ip, uint8_t* message, Ptr<Socket> socket);
    static void EncourageDocmentSucc(Address ip, uint8_t* message, Ptr<Socket> socket);
    static void EncourageValidateSucc(Address ip, uint8_t* message, Ptr<Socket> socket);

    static void AddIp(uint8_t* message, uint8_t *ip, uint8_t* send_buff, int *len);
    static uint8_t* GetIp(uint8_t* message);
    // static void AddPort(uint8_t* message, short port, char* send_buff, int *len);
};
}
#endif
