#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ev.h>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libev.h"

void connectCallback(const redisAsyncContext *ctx, int status)
{
        if (status != REDIS_OK)
                printf("Error: %s\n", ctx->errstr);
        else printf("Connected...\n");
}

void disconnectCallback(const redisAsyncContext *ctx, int status)
{
        if (status != REDIS_OK)
                printf("Error: %s\n", ctx->errstr);
        else printf("Disconnected...\n");
}

void getCallback(redisAsyncContext *ctx, void *r, void *privdata)
{
        redisReply *reply = r;
        if (reply == NULL) return;
        printf("%s : %s\n", (char*)privdata, reply->str);
        redisAsyncDisconnect(ctx);
}

int main()
{
        signal(SIGPIPE, SIG_IGN);

        redisAsyncContext *ctx = redisAsyncConnect("127.0.0.1", 6379);
        if (ctx->err) {
                printf("Error: %s\n", ctx->errstr);
                return 1;
        }

        redisLibevAttach(EV_DEFAULT_ ctx);

        /* register callbacks */
        redisAsyncSetConnectCallback(ctx, connectCallback);
        redisAsyncSetDisconnectCallback(ctx, disconnectCallback);

        /* send commands */
        redisAsyncCommand(ctx, NULL, NULL, "SET key 10");
        redisAsyncCommand(ctx, getCallback, (char*)"end-1", "GET key");

        ev_loop(EV_DEFAULT_ 0);

        return 0;
}
