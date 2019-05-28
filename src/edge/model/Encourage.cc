#include "Encourage.h"
#include "MessageClassifier.h"
#include <vector>
#include <stdlib.h>
#include <string.h>
#define cloud_ip "10.1.1.2"
 namespace ns3{
Encourage::Encourage()
{

}

void Encourage::EncourageDocument(Address ip, uint8_t* message, Ptr<Socket> socket)
{
    // uint8_t* send_buff=new uint8_t[100];
    int len=strlen((char*)message);
    // std::cout <<len<<std::endl;
    // memcpy(send_buff,message,len);
    uint8_t* u_ip=ip.m_data;

    AddIp(message, u_ip, message,&len);
    // AddPort(message,(short) port, send_buff, &len);

    len=std::strlen((char*)message);
    Ptr<Packet> packet=Create<Packet> (message, len+1);
    from.m_data[0]=10;
    from.m_data[1]=1;
    from.m_data[2]=1;
    from.m_data[3]=2;
    socket->SendTo(packet, 0, from);

    //Communication::Send_To(send_buff,cloud_ip,cloud_port);

    // free(send_buff);
}


void Encourage::EncourageValidate(Address ip, uint8_t* message, Ptr<Socket> socket){
  int len=strlen((char*)message);
  uint8_t* u_ip=ip.m_data;
  AddIp(message, u_ip, message,&len);

  len=std::strlen((char*)message);
  Ptr<Packet> packet=Create<Packet> (message, len+1);
  from.m_data[0]=10;
  from.m_data[1]=1;
  from.m_data[2]=1;
  from.m_data[3]=2;
  socket->SendTo(packet, 0, from);
}

void Encourage::EncourageDocmentSucc(Address ip, uint8_t* message, Ptr<Socket> socket){
  int len=std::strlen((char*)message);
  std::cout <<"before len is "<<len<<std::endl;
  uint8_t* to=GetIp(message);
  len=std::strlen((char*)message);
  std::cout <<"after len is "<<len<<std::endl;

  Ptr<Packet> packet=Create<Packet> (message, len+1);//packet
  // std::cout <<"ip is "<<to<<std::endl;
  from.m_data[0]=to[0];
  from.m_data[1]=to[1];
  from.m_data[2]=to[2];
  from.m_data[3]=to[3];
  Address cloud(3,to, std::strlen((char*)to));//ip
  socket->SendTo(packet, 0, from);//send
}


void Encourage::EncourageValidateSucc(Address ip, uint8_t* message, Ptr<Socket> socket){
  int len=std::strlen((char*)message);
  std::cout <<"before len is "<<len<<std::endl;
  uint8_t* to=GetIp(message);
  len=std::strlen((char*)message);
  std::cout <<"after len is "<<len<<std::endl;

  Ptr<Packet> packet=Create<Packet> (message, len+1);//packet
  // std::cout <<"ip is "<<to<<std::endl;
  from.m_data[0]=to[0];
  from.m_data[1]=to[1];
  from.m_data[2]=to[2];
  from.m_data[3]=to[3];
  socket->SendTo(packet, 0, from);//send
}



uint8_t* Encourage::GetIp(uint8_t* message){
  int len=0;
  char MT_BT;
  int ML;
  uint8_t* ip=new uint8_t[4];
  std::string ip_str="";
  // char* ip_c=new char[20];

  memcpy(&MT_BT, &message[len++], 1);
  memcpy(&ML, &message[len], 4);
  len+=4;
  len+=ML;
  for(int i=0; i<4;i++){
    memcpy(&ip[i], &message[len], 1);
    len++;
    // sprintf(ip_str[i],"%s",int(ip[i]));
    // ip_str=ip_str+std::to_string(int(ip[i]));
    // if(i<3){
    //   ip_str=ip_str+".";
    // }
  }
  // std::strcpy(ip_c,ip_str.c_str());
  len-=4;
  memset(&message[len],'\0', 4);
  return ip;



}



void Encourage::AddIp(uint8_t *message,uint8_t* ip, uint8_t *send_buff, int* len)
{
    uint8_t ip_4_c[4];
    int ip_4[4];
    char* end;

    //ML=ML+4
    int temp_len=1;
    int ML=*len+4;
    memcpy(&message[temp_len],&ML, 4);


    std::vector<std::string> ip_4_str= MessageClassifier::ip2int((char*)ip);
    for(int i=0;i<4;i++){
        sscanf(ip_4_str[i].c_str(),"%d",&ip_4[i]);
        ip_4_c[i]=(uint8_t)(ip_4[i]);
        std::cout<<ip_4_c[i]<<" and "<<((int)ip_4_c[i])<<std::endl;
    }




    for(int i=0;i<4;i++){
        memcpy(&send_buff[*len],&ip_4_c[i], 1);
        (*len)++;
        std::cout<<"this is "<<strlen((char*)send_buff)<<std::endl;
    }
    std::cout<<"this is "<<*len<<std::endl;
}

// void Encourage::AddPort(uint8_t *message, short int port, char *send_buff, int *len)
// {
//     memcpy(&send_buff[(*len)],&port, 2 );
//     (*len)+=2;
// //    std::cout<<"this is "<<strlen(send_buff)<<std::endl;
// //    memcpy(&port,&send_buff[*(len)-2],1);
// //    std::cout<<"this is port "<<port<<std::endl;
// }




}
