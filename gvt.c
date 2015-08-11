#include <stdbool.h>
#include <string.h>
#include "gvt.h"

#define GVT_VERSION  1
#define GVT_IMEI     2
#define GVT_NAME     3
#define GVT_RT_ST    4
#define GVT_DATE     5
#define GVT_TIME     6
#define GVT_FIX_A_V  7
#define GVT_LATITUDE 8

static bool check(char **c, char expected)
{
        if (**c == expected) {
                (*c)++;
                return true;
        }
        return false;
}

static bool fill(int fieldNum, char *buff, struct gvtData *gvtData)
{
        switch (fieldNum) {
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
        }
        return true;
}

static bool extract(int fieldNum, char **c, struct gvtData *gvtData)
{
        char buff[128];
        int i;
        for (i = 0; i < 128 && **c != ','; i++, (*c)++)
                buff[i] = **c;
        (*c)++;
        buff[i] = 0;

        return fill(fieldNum, buff, gvtData);
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

        return result;
}
