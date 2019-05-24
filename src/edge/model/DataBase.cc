#include "DataBase.h"
#include "iostream"
#include <string.h>
//#include "Debug.h"
#define MODUEL "DataBase"
using namespace std;

DataBase::DataBase(){
    timeout.tv_sec=2;
    timeout.tv_usec=0;
}

int DataBase::AsynConnect(){
//    pRedisAsyContext = redisAsyncConnect("127.0.0.1", 6379);
//    if ( (NULL == pRedisAsyContext) || (pRedisAsyContext->err) )
//        {
//            if (pRedisAsyContext)
//            {
//                std::cout << "connect error:" << pRedisAsyContext->errstr << std::endl;
//            }
//            else
//            {
//                std::cout << "connect error: can't allocate redis context." << std::endl;
//            }

//            return -1;
//        }
    return 1;
}

int DataBase::SynConnect(){
//    struct timeval timeout1 = {2, 0};
//    pRedisContext = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
//    if ( (NULL == pRedisContext) || (pRedisContext->err) )
//        {
//            if (pRedisContext)
//            {
//                std::cout << "connect error:" << pRedisContext->errstr << std::endl;
//            }
//            else
//            {
//                std::cout << "connect error: can't allocate redis context." << std::endl;
//            }
//            return -1;
//        }
//    if(ExistKey("Three")){
//        Debug::Log("Database","key three exists");
//    }
//    else{
//        if(!SetKey("three","hhh")){
//            cout <<"set failed"<<endl;
//        }
//        else{
//            if(ExistKey("three")){
//                cout << "key three exists"<<endl;
//                char* three=GetKey("three");
//                cout <<"three is "<<three<<endl;
//                if(DelKey("four")){
//                    cout << "del key three succ"<<endl;
//                    ExistKey("three");
//                    GetKey("three");

//                }
//            }

//        }
//    }
//    Publish("one","888");
//    Subscribe("one");




//    FreeRedisReply(pRedisReply);
//    FreeRedis();
    return 1;
}


void DataBase::FreeRedisReply(redisReply * reply){// free the reply object
//    freeReplyObject(reply);
}

void DataBase::FreeRedis()
{
//    redisFree(pRedisContext);
}



bool DataBase::ExistKey(char* key){//check if the key exists
//    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "exists %s", key);
//    if(pRedisContext->err!=0){
////        std::cout<<"err happens"<<std::endl;
//        FreeRedisReply(pRedisReply);
//        return false;
//    }
//    else{
//        if(pRedisReply->integer>0){
////            std::cout << "key "<<key<<"exists"<<std::endl;
//            FreeRedisReply(pRedisReply);
//            return true;
//        }
////        std::cout << "key "<<key<<" not exists"<<std::endl;
//    }
//    FreeRedisReply(pRedisReply);
    return false;
}


bool DataBase::SetKey(char* key, char* value){
//    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "set %s %s", key, value);
//    std::cout <<"here"<< std::endl;
////    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "set one hh");
//    if(pRedisContext->err!=0){
////        std::cout<<"err happens"<<std::endl;
//        FreeRedisReply(pRedisReply);
//        return false;
//    }
//    else{

//        if(strcmp(pRedisReply->str, "OK")==0){
////            std::cout << "key "<<key<<" set succ"<<std::endl;
//            FreeRedisReply(pRedisReply);
//            return true;
//        }
////        std::cout << "key "<<pRedisReply->str<<" set failed"<<std::endl;
//    }
//    FreeRedisReply(pRedisReply);
    return false;
}



char* DataBase::GetKey(char*key){
//    char* reply= new char[100];
//    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "get %s", key);
//    if(pRedisContext->err!=0){
////        std::cout<<"err happens"<<std::endl;
//        FreeRedisReply(pRedisReply);
//        return NULL;
//    }
//    else{
//        if(pRedisReply->len>0){
////            std::cout << "key "<<key<<" is "<<pRedisReply->str<<std::endl;
//            strcpy(reply,pRedisReply->str);
//            FreeRedisReply(pRedisReply);
//            return reply;
//            //attention, here we use FreeRedisReply to free the pointer of REdisReply
//            //so the pRedisReply-> will be freed at tehe same time
//            //to save the value, i introduce another pointer reply, and teh pointer value will be returned as result
//        }
////        std::cout << "key "<<key<<" get failed"<<std::endl;
//    }
//    FreeRedisReply(pRedisReply);
    return NULL;
}


bool DataBase::DelKey(char* key){
//    if(ExistKey(key)){
//        redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "del %s", key);
//        if(pRedisContext->err!=0){
////            std::cout<<"err happens"<<std::endl;
//            FreeRedisReply(pRedisReply);
//            return false;
//        }
//        else{
//            if(pRedisReply->integer>0){
////                std::cout << "key "<<key<<" is "<<pRedisReply->str<<std::endl;
//                FreeRedisReply(pRedisReply);
//                return true;
//            }
//            std::cout << "key "<<key<<" del failed"<<std::endl;
//            FreeRedisReply(pRedisReply);
//            return false;
//        }
//    }
//    else{
//        cout << "key not exists"<<endl;
//        return false;
//    }
}

bool DataBase::Publish(char* channel, char* message){
//    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "publish %s %s", channel, message);
//    if(pRedisContext->err!=0){
////        std::cout<<"err happens"<<std::endl;
//        FreeRedisReply(pRedisReply);
//        return NULL;
//    }
//    else{
//        if(pRedisReply->integer > 0){
//            FreeRedisReply(pRedisReply);
//            return true;
//        }
//        Debug::Log(MODUEL,"no such channel");
////        std::cout << "key "<<key<<" get failed"<<std::endl;
//    }
//    FreeRedisReply(pRedisReply);
    return false;
}




char* DataBase::Subscribe(char* channel){
////    redisReply *pRedisReply = (redisReply*)redisAsyCommand(pRedisContext, "SUBSCRIBE %s", channel);
//    int ret  = redisAsyncCommand(pRedisAsyContext, &DataBase::CallBackSub, this, "SUBSCRIBE %s", channel);
//    if (REDIS_ERR == ret)
//        {
//            printf("Subscribe command failed: %d\n", ret);
//            return NULL;
//        }

    return NULL;
}


void DataBase::CallBackSub(struct redisAsyncContext *redis_context, void *reply, void *privdata){
//    cout << "recv" <<endl;
}




bool DataBase::ExpireKey(char *key, int ttl){
//    redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext, "expire %s %d", key, ttl);
//    if(pRedisContext->err!=0){
////        std::cout<<"err happens"<<std::endl;
//        FreeRedisReply(pRedisReply);
//        return NULL;
//    }
//    else{
//        if(pRedisReply->integer > 0){
//            FreeRedisReply(pRedisReply);
//            return true;
//        }
//        Debug::Log(MODUEL,"no such key");
////        std::cout << "key "<<key<<" get failed"<<std::endl;
//    }
//    FreeRedisReply(pRedisReply);
    return false;
}



