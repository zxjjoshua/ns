#ifndef __messageclassifier__
#define __messageclassifier__
#include "DataBase.h"
#include <stdlib.h>
#include <vector>
#include "ns3/ipv4-address.h"
#include <stdint.h>
#include "ns3/socket.h"
#include "ns3/packet.h"

namespace ns3{

class Socket;
class Packet;

class MessageClassifier
{
public:
    MessageClassifier();
//    MessageProcess();
    static void Router(uint8_t* message, Address from, Ptr<Socket> socket);
    static std::vector<std::string> ip2int(char* ip);

};
}

#endif
