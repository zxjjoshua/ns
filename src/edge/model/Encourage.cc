#include "Encourage.h"
#include "MessageClassifier.h"
#include <vector>
#include <stdlib.h>
#include <string.h>

 namespace ns3{
Encourage::Encourage()
{

}

void Encourage::EncourageDocument(Address ip, uint8_t* message)
{
    uint8_t* send_buff=new uint8_t[100];
    int len=strlen((char*)message);
    std::cout <<len<<std::endl;
    memcpy(send_buff,message,len);
    uint8_t* u_ip=InetSocketAddress::ConvertFrom (from).GetIpv4 ();

    AddIp(message, u_ip, send_buff,&len);
    // AddPort(message,(short) port, send_buff, &len);


    //Communication::Send_To(send_buff,cloud_ip,cloud_port);

    free(send_buff);
}

void Encourage::AddIp(char *message,char* ip, char *send_buff, int* len)
{
    char ip_4_c[4];
    int ip_4[4];
    char* end;
    std::vector<std::string> ip_4_str= MessageClassifier::ip2int(ip);
    for(int i=0;i<4;i++){
        sscanf(ip_4_str[i].c_str(),"%d",&ip_4[i]);
        ip_4_c[i]=(char)(ip_4[i]);
        std::cout<<ip_4_c[i]<<" and "<<((int(ip_4_c[i])+256)%256)<<std::endl;
    }

    for(int i=0;i<4;i++){
        memcpy(&send_buff[*len],&ip_4_c[i], 1);
        (*len)++;
        std::cout<<"this is "<<strlen(send_buff)<<std::endl;
    }
    std::cout<<"this is "<<*len<<std::endl;
}

void Encourage::AddPort(char *message, short int port, char *send_buff, int *len)
{
    memcpy(&send_buff[(*len)],&port, 2 );
    (*len)+=2;
//    std::cout<<"this is "<<strlen(send_buff)<<std::endl;
//    memcpy(&port,&send_buff[*(len)-2],1);
//    std::cout<<"this is port "<<port<<std::endl;
}




}
