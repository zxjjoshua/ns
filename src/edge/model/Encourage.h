#ifndef __encourage__
#define __encourage__
#include "DataBase.h"
#define cloud_ip "12.3.2.21"
#define cloud_port 3232

namespace ns3 {
class MessageClassifier;
class Encourage
{
public:
    Encourage();
    static void EncourageDocument(DataBase* db, char* ip, int port, char* message);
    static void EncourageValidate( DataBase* db, char* ip, int port, char* message);
    static void EncourageDocmentSucc(DataBase* db, char* ip, int port, char* message);
    static void EncourageValidateSucc( DataBase* db, char* ip, int port, char* message);

    static void AddIp(char* message, char *ip, char* send_buff, int *len);
    static void AddPort(char* message, short port, char* send_buff, int *len);
};
}
#endif
