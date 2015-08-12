#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ev.h>

#include "reg-ev.h"

int main()
{
        registerRedis();
        registerTcp();

        ev_loop(EV_DEFAULT_ 0);
        return 0;
}



