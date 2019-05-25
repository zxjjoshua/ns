#ifndef __messageclassifier__
#define __messageclassifier__
#include "DataBase.h"
#include <stdlib.h>
#include <vector>
#include "ns3/ipv4-address.h"
#include <stdint.h>


namespace ns3{

class Socket;
class Packet;

class MessageClassifier
{
public:
    MessageClassifier();
//    MessageProcess();
    static void Router(char* message, Address from, Ptr<Socket> socket);
    static std::vector<std::string> ip2int(char* ip);

};
}

#endif
