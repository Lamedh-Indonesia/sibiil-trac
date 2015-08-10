#include <stdio.h>
#include <string.h>
#include "gvt.h"

static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define test_cond(_c) if(_c) printf("\033[0;32mPASSED\033[0;0m\n"); else {printf("\033[0;31mFAILED\033[0;0m\n"); fails++;}

void extractGvtTest()
{
        char* gvtStr = "$MGV002,860719020193193,DeviceName,R,240214,104742,A,2238.20471,"
                "N,11401.97967,E,00,03,00,1.20,0.462,356.23,137.9,1.5,460,07,262C,"
                "0F54,25,0000,0000,0,0,0,28.5,28.3,,,100,Timer;!";

        test("Extract GVT string");
        struct gvtData data;
        gvtExtract(gvtStr, &data);
        test_cond(strcmp(data.imei, "860719020193193") == 0);
}

int main()
{
        extractGvtTest();
        return 0;
}
