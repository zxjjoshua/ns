#ifndef __messageclassifier__
#define __messageclassifier__
#include "DataBase.h"
#include <stdlib.h>
#include <vector>
#include "ns3/ipv4-address.h"
#include <stdint.h>

class MessageClassifier
{
public:
    MessageClassifier();
//    MessageProcess();
    static void Router(char* message, Adress from);
    static std::vector<std::string> ip2int(char* ip);

};


#endif

