#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gvt.h"

#define GVT_VERSION            1
#define GVT_IMEI               2
#define GVT_NAME               3
#define GVT_RT_ST              4
#define GVT_DATE               5
#define GVT_TIME               6
#define GVT_FIX_A_V            7
#define GVT_LATITUDE           8
#define GVT_NS                 9
#define GVT_LONGITUDE         10
#define GVT_WE                11
#define GVT_USED_BPS          12
#define GVT_USED_GPS          13
#define GVT_USED_GLONASS      14
#define GVT_HDOP              15
#define GVT_SPEED             16
#define GVT_COURSE            17
#define GVT_ALTITUDE          18
#define GVT_MILEAGE           19
#define GVT_MCC               20
#define GVT_MNC               21
#define GVT_LAC               22
#define GVT_CELLID            23
#define GVT_GSM_SIGNAL        24
#define GVT_DIGITAL_IN_FLAGS  25
#define GVT_DIGITAL_OUT_FLAGS 26
#define GVT_ANALOG1           27
#define GVT_ANALOG2           28
#define GVT_ANALOG3           29
#define GVT_TEMPERATURE1      30
#define GVT_TEMPERATURE2      31
#define GVT_BATTERY           32
#define GVT_ALERT             33

static bool check(char **c, char expected)
{
        if (**c == expected) {
                (*c)++;
                return true;
        }
        return false;
}

static bool skipField(char **c)
{
        while (**c != ',')
                (*c)++;
        (*c)++;
        return true;
}

static bool fill(int gvtField, char *buff, struct gvtData *gvtData)
{
        switch (gvtField) {
        case GVT_VERSION:
                strcpy(gvtData->version, buff);
                break;
        case GVT_IMEI:
                strcpy(gvtData->imei, buff);
                break;
        case GVT_NAME:
                strcpy(gvtData->name, buff);
                break;
        case GVT_RT_ST:
                gvtData->RS = *buff;
                break;
        case GVT_DATE:
                strcpy(gvtData->date, buff);
                break;
        case GVT_TIME:
                strcpy(gvtData->time, buff);
                break;
        case GVT_FIX_A_V:
                gvtData->fixable = *buff;
                break;
        case GVT_LATITUDE:
                strcpy(gvtData->latitude, buff);
                break;
        case GVT_NS:
                gvtData->NS = *buff;
                break;
        case GVT_LONGITUDE:
                strcpy(gvtData->longitude, buff);
                break;
        case GVT_WE:
                gvtData->WE = *buff;
                break;
        case GVT_USED_BPS:
                strcpy(gvtData->usedBds, buff);
                break;
        case GVT_USED_GPS:
                strcpy(gvtData->usedGps, buff);
                break;
        case GVT_USED_GLONASS:
                strcpy(gvtData->usedGlonass, buff);
                break;
        case GVT_HDOP:
                gvtData->hdop = atof(buff);
                break;
        case GVT_SPEED:
                gvtData->speed = atof(buff);
                break;
        case GVT_COURSE:
                gvtData->course = atof(buff);
                break;
        case GVT_ALTITUDE:
                gvtData->altitude = atof(buff);
                break;
        case GVT_MILEAGE:
                gvtData->mileage = atof(buff);
                break;
        case GVT_MCC:
                strcpy(gvtData->mcc, buff);
                break;
        case GVT_MNC:
                strcpy(gvtData->mnc, buff);
                break;
        case GVT_LAC:
                strcpy(gvtData->lac, buff);
                break;
        case GVT_CELLID:
                strcpy(gvtData->cellId, buff);
                break;
        case GVT_GSM_SIGNAL:
                gvtData->gsmSignal = atoi(buff);
                break;
        case GVT_DIGITAL_IN_FLAGS:
                gvtData->digitalInFlags = atoi(buff);
                break;
        case GVT_DIGITAL_OUT_FLAGS:
                gvtData->digitalOutFlags = atoi(buff);
                break;
        case GVT_ANALOG1:
                gvtData->analog1 = atoi(buff);
                break;
        case GVT_ANALOG2:
                gvtData->analog2 = atoi(buff);
                break;
        case GVT_ANALOG3:
                gvtData->analog3 = atoi(buff);
                break;
        case GVT_TEMPERATURE1:
                gvtData->temperature1 = atof(buff);
                break;
        case GVT_TEMPERATURE2:
                gvtData->temperature2 = atof(buff);
                break;
        case GVT_BATTERY:
                gvtData->battery = atoi(buff);
                break;
        case GVT_ALERT:
                strcpy(gvtData->alert, buff);
                break;
        default:
                return false;
        }
        return true;
}

static bool extract(int gvtField, char **c, struct gvtData *gvtData)
{
        char buff[128];
        int i;
        for (i = 0; i < 128 && **c != ','; i++, (*c)++)
                buff[i] = **c;
        (*c)++;
        buff[i] = 0;

        return fill(gvtField, buff, gvtData);
}

bool gvtExtract(char* gvtStr, struct gvtData *gvtData)
{
        bool result = true;
        char *c = gvtStr;
        result = check(&c, '$');
        result &= extract(GVT_VERSION, &c, gvtData);
        result &= extract(GVT_IMEI, &c, gvtData);
        result &= extract(GVT_NAME, &c, gvtData);
        result &= extract(GVT_RT_ST, &c, gvtData);
        result &= extract(GVT_DATE, &c, gvtData);
        result &= extract(GVT_TIME, &c, gvtData);
        result &= extract(GVT_FIX_A_V, &c, gvtData);
        result &= extract(GVT_LATITUDE, &c, gvtData);
        result &= extract(GVT_NS, &c, gvtData);
        result &= extract(GVT_LONGITUDE, &c, gvtData);
        result &= extract(GVT_WE, &c, gvtData);
        result &= extract(GVT_USED_BPS, &c, gvtData);
        result &= extract(GVT_USED_GPS, &c, gvtData);
        result &= extract(GVT_USED_GLONASS, &c, gvtData);
        result &= extract(GVT_HDOP, &c, gvtData);
        result &= extract(GVT_SPEED, &c, gvtData);
        result &= extract(GVT_COURSE, &c, gvtData);
        result &= extract(GVT_ALTITUDE, &c, gvtData);
        result &= extract(GVT_MILEAGE, &c, gvtData);
        result &= extract(GVT_MCC, &c, gvtData);
        result &= extract(GVT_MNC, &c, gvtData);
        result &= extract(GVT_LAC, &c, gvtData);
        result &= extract(GVT_CELLID, &c, gvtData);
        result &= extract(GVT_GSM_SIGNAL, &c, gvtData);
        result &= extract(GVT_DIGITAL_IN_FLAGS, &c, gvtData);
        result &= extract(GVT_DIGITAL_OUT_FLAGS, &c, gvtData);
        result &= extract(GVT_ANALOG1, &c, gvtData);
        result &= extract(GVT_ANALOG2, &c, gvtData);
        result &= extract(GVT_ANALOG3, &c, gvtData);
        result &= extract(GVT_TEMPERATURE1, &c, gvtData);
        result &= extract(GVT_TEMPERATURE2, &c, gvtData);
        skipField(&c); /* reserved RFID */
        skipField(&c); /* reserved external accessories */
        result &= extract(GVT_BATTERY, &c, gvtData);
        result &= extract(GVT_ALERT, &c, gvtData);
        result &= check(&c, ';');
        result &= check(&c, '!');
        return result;
}

void genRedisInsertCommand(char *command, struct gvtData *gvtData, unsigned int sequence)
{
        char key[25];
        sprintf(key, "gvt:%s:%d", gvtData->imei, sequence);
        sprintf(command, "hmset %s version \"%s\" "
                "imei \"%s\" "
                "name \"%s\" "
                "RS %c "
                "date \"%s\" "
                "time \"%s\" "
                "fixable %c "
                "latitude \"%s\" "
                "NS %c "
                "longitude \"%s\" "
                "WE %c "
                "usedBds \"%s\" "
                "usedGps \"%s\" "
                "usedGlonass \"%s\" ",
                key, gvtData->version, gvtData->imei, gvtData->name, gvtData->RS, gvtData->date,
                gvtData->time, gvtData->fixable, gvtData->latitude, gvtData->NS, gvtData->longitude,
                gvtData->WE, gvtData->usedBds, gvtData->usedGps, gvtData->usedGlonass);
}
