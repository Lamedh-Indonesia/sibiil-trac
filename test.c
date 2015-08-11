#include <stdio.h>
#include <string.h>
#include "gvt.h"

static int tests = 0, fails = 0;
#define test(_s) { printf("#%02d %s ", ++tests, _s); }
#define test_cond(_c) if(_c) printf("\033[0;32mPASSED\033[0;0m\n"); else {printf("\033[0;31mFAILED\033[0;0m\n"); fails++;}
#define expect(_s, _c) { test(_s); test_cond(_c); }

void testExtractGvt(char* version, char *imei, char *name, char RS,
                    char date[7], char time[7], char fixable,
                    char latitude[11], char NS,
                    char longitude[13], char WE,
                    char usedBds[3], char usedGps[3], char usedGlonass[3],
                    float hdop, float speed, float course, float altitude, float mileage,
                    char mcc[4], char mnc[3], char lac[5], char cellId[5],
                    char gsmSignal,
                    char digitalInFlags, char digitalOutFlags,
                    short analog1, short analog2, short analog3,
                    float temperature1, float temperature2,
                    /* char rfid,         /\* (reserved) RFID *\/ */
                    /* char external,     /\* (reserved) external accessories status *\/ */
                    char battery, char alert[25])
                    /* char checksum,      /\* (reserved) checksum *\/ */
{
        struct gvtData data;
        char gvtStr[512];
        sprintf(gvtStr, "$%s,%s,%s,%c,%s,%s,%c,%s,%c,%s,%c,%s,%s,%s,%f,%f,%f,%f,%f," /* mileage */
                "%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%f,%f,,,%d,%s,;!",
                version, imei, name, RS, date, time, fixable, latitude, NS, longitude, WE, usedBds, usedGps, usedGlonass,
                hdop, speed, course, altitude, mileage, mcc, mnc, lac, cellId, gsmSignal, digitalInFlags, digitalOutFlags,
                analog1, analog2, analog3, temperature1, temperature2, battery, alert);

        gvtExtract(gvtStr, &data);

        expect("version", strcmp(data.version, version) == 0);
        expect("imei", strcmp(data.imei, imei) == 0);
        expect("name", strcmp(data.name, name) == 0);
        expect("RS", data.RS == RS);
        expect("date", strcmp(data.date, date) == 0);
        expect("time", strcmp(data.time, time) == 0);
        expect("fixable", data.fixable == fixable);
        expect("latitude", strcmp(data.latitude, latitude) == 0);
}

int main()
{
        testExtractGvt("MGV002", "860719020193193", "DeviceName", 'R',
                       "240214", "104742", 'A', "2238.20471",
                       'N', "11401.97967", 'E', "00", "03", "00", 1.20f,
                       0.462f, 356.23f, 137.9f, 1.5f, "460", "07", "262C",
                       "0F54", 25, 0, 0, 0, 0, 0, 28.5f,
                       28.3f, 100, "Timer");

        testExtractGvt("MGV002", "860719020193360", "DeviceName2", 'S',
                       "240214", "104742", 'A', "2238.20471",
                       'N', "11401.97967", 'E', "00", "03", "00", 1.20f,
                       0.462f, 356.23f, 137.9f, 1.5f, "460", "07", "262C",
                       "0F54", 25, 0, 0, 0, 0, 0, 28.5f,
                       28.3f, 100, "Timer");
        return 0;
}
