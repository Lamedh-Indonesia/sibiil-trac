#ifndef GVT_H
#define GVT_H

#include <stdbool.h>

struct gvtData {
        char version[7];      /* protocol version */
        char imei[16];        /* device IMEI */
        char name[16];        /* device name */
        char RS;              /* GPRS real-time/stored data flag */
        char date[7];         /* date */
        char time[7];         /* time */
        char fixable;         /* GPS fixed flag */

        char latitude[11];    /* latitude */
        char NS;              /* north or south */
        char longitude[13];   /* longitude */
        char WE;              /* west or east? */

        char usedBds[3];      /* used satellite number of BDS */
        char usedGps[3];      /* used satellite number of GPS */
        char usedGlonass[3];  /* used satellite number of GLONASS */

        float hdop;           /* HDOP */
        float speed;          /* speed */
        float course;         /* course */
        float altitude;       /* altitude */
        float mileage;        /* mileage */

        char mcc[4];          /* Mobile country code. */
        char mnc[3];          /* Mobile network code. */
        char lac[5];          /* Location area code */
        char cellId[5];       /* Cell ID */
        char gsmSignal;       /* GSM signal strength */
        char digitalInFlags;  /* digital input */
        char digitalOutFlags; /* digital output */
        short analog1;        /* analog input 1 */
        short analog2;        /* analog input 2 */
        short analog3;        /* analog input 3 */
        float temperature1;   /* temperature sensor 1 */
        float temperature2;   /* temperature sensor 2 */
        /* char rfid;         /\* (reserved) RFID *\/ */
        /* char external;     /\* (reserved) external accessories status *\/ */
        char battery;         /* battery level */
        char alert[25];       /* alert event type */
        /* char checksum;     /\* (reserved) checksum *\/ */
};

bool gvtExtract(char *gvtStr, struct gvtData *gvtData);
void genRedisInsertCommand(char *command, struct gvtData *gvtData, unsigned int sequence);

#endif /* GVT_H */
