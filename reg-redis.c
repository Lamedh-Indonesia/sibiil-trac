#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libev.h"
#include "reg-ev.h"

redisAsyncContext *redisCtx;

static void connectHandler(const redisAsyncContext *redisCtx, int status)
{
        if (status != REDIS_OK) printf("Error: %s\n", redisCtx->errstr);
        else printf("Connected to redis...\n");
}

static void disconnectHandler(const redisAsyncContext *redisCtx, int status)
{
        if (status != REDIS_OK) printf("Error: %s\n", redisCtx->errstr);
        else printf("Disconnected to redis...\n");
}

bool registerRedis()
{
        signal(SIGPIPE, SIG_IGN);
        redisCtx = redisAsyncConnect("127.0.0.1", 6379);
        if (redisCtx->err) {
                printf("Error: %s\n", redisCtx->errstr);
                return false;
        }
        redisLibevAttach(EV_DEFAULT_ redisCtx);
        redisAsyncSetConnectCallback(redisCtx, connectHandler);
        redisAsyncSetDisconnectCallback(redisCtx, disconnectHandler);
        return true;
}

/* static void getHandler(redisAsyncContext *redisCtx, void *r, void *privdata); */
