#include <strings.h>
#include <ev.h>
#include <unistd.h>
#include <netinet/in.h>
#include <malloc.h>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "ht.h"
#include "reg-ev.h"
#include "gvt.h"

#define BUFFER_SIZE 1024

extern redisAsyncContext *redisCtx;
static int totalClients;

static struct hashtable* htImeiSequence;

static void readHandler(EV_P_ struct ev_io *watcher, int revents)
{
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }
        char buffer[BUFFER_SIZE];
        int n = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
        int i;
        for (i = 0; i < n; i++)
                if (buffer[i] == '\n') buffer[i] = 0;
        if (n < 0) {
                perror("read error");
                return;
        }
        if (n == 0) {
                ev_io_stop(loop, watcher);
                close(watcher->fd);
                free(watcher);
                printf("Client closed, %d client(s) connected.\n", --totalClients);
                return;
        }
        else printf("Client sended: %s\n", buffer);

        struct gvtData gvtData;
        gvtExtract(buffer, &gvtData);
        printf("Received from %s\n", gvtData.name);

        int *res = (int*)htGet(htImeiSequence, gvtData.imei);
        int sequence = res == NULL? 1 : *res;
        printf("%d %s\n", sequence, gvtData.imei);
        char command[256];
        genRedisInsertCommand(command, &gvtData, sequence++);
        printf("sending to redis: %s\n", command);
        redisAsyncCommand(redisCtx, NULL, NULL, command);
        printf("set %s %d\n", gvtData.imei, sequence);
        htSet(htImeiSequence, gvtData.imei, &sequence, sizeof(int));
        printf("%d\n", sizeof(int));
}

static void acceptHandler(EV_P_ struct ev_io *watcher, int revents)
{
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }
        int sd = accept(watcher->fd, NULL, NULL);
        printf("%d client(s) connected.\n", ++totalClients);

        // register readHandler that will be called when client send any data
        struct ev_io *newWatcher = (struct ev_io*) malloc(sizeof(struct ev_io));
        ev_io_init(newWatcher, readHandler, sd, EV_READ);
        ev_io_start(loop, newWatcher);
}

bool registerTcp()
{
        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8088);
        addr.sin_addr.s_addr = INADDR_ANY;

        int serverSd = socket(PF_INET, SOCK_STREAM, 0);
        if (serverSd < 0) printf("socket() failed");
        bind(serverSd, (struct sockaddr*) &addr, sizeof(addr));
        listen(serverSd, 2);
        printf("listening to %d\n", 8088);

        htImeiSequence = htCreate(1 << 16); /* 64K bytes hash table */

        struct ev_io *watcher = (struct ev_io*) malloc(sizeof(struct ev_io)); // watcher for new connection
        ev_io_init(watcher, acceptHandler, serverSd, EV_READ); // bind the watcher to the handler
        ev_io_start(EV_DEFAULT_ watcher); // register the watcher to the event loop

        return true;
}
