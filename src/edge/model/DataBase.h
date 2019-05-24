#ifndef __database__
#define __database__
#include <stdio.h>
#include <iostream>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#define REDIS_PORT 6379

class DataBase{
public:
    DataBase();
    int SynConnect();
    int AsynConnect();
    void FreeRedisReply(redisReply * reply);
    void FreeRedis();

    bool ExistKey(char* key);
    bool SetKey(char* key, char* value);
    char* GetKey(char*key);
    bool DelKey(char* key);
    bool ExpireKey(char *key, int ttl);

    bool Publish(char* channel, char* message);
    char* Subscribe(char* channel);

    static void CallBackSub(struct redisAsyncContext *redis_context, void *reply, void *privdata);
    //回调函数必须要是static

private:
    struct timeval timeout;
    redisContext *pRedisContext;
    redisAsyncContext* pRedisAsyContext;
};

#endif

