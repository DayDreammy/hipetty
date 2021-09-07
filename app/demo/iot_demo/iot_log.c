
/*
 * Copyright (c) 2020 HiHope Community.
 * Description: IoT platform
 * Author: HiSpark Product Team
 * Create: 2020-5-20
 */

#include <iot_log.h>
#include <string.h>
#include <stdio.h>

static en_iot_log_level_t gIoTLogLevel = EN_IOT_LOG_LEVEL_TRACE;
/*Log rank array*/
static const char *gIoTLogLevelNames[] =
{
    "TRACE",
    "DEBUG",
    "INFO ",
    "WARN ",
    "ERROR",
    "FATAL"
};
/*Log level setting*/
int IoTLogLevelSet(en_iot_log_level_t level)
{
    int ret = -1;
    if(level < EN_IOT_LOG_LEVEL_MAX ){
        gIoTLogLevel = level;
        ret = 0;
    }
    return ret;
}
/*Log level acquisition*/
en_iot_log_level_t IoTLogLevelGet(void)
{
    return gIoTLogLevel;
}
/*Log rank name acquisition*/
const char *IoTLogLevelGetName(en_iot_log_level_t log_level)
{
    if (log_level >= EN_IOT_LOG_LEVEL_MAX){
        return "NULL ";
    }
    else{
        return gIoTLogLevelNames[log_level];
    }

}
