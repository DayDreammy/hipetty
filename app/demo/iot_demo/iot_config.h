/*
 * Copyright (c) 2020 HiHope Community.
 * Description: IoT Platform 
 * Author: HiSpark Product Team.
 * Create: 2020-6-20
 */

#ifndef IOT_CONFIG_H_
#define IOT_CONFIG_H_

///<CONFIG THE LOG
/*if you need the iot log for the development , please enable it, else please comment it*/
#define CONFIG_LINKLOG_ENABLE   1

///< CONFIG THE WIFI
/* Please modify the ssid and pwd for the own */
#define CONFIG_AP_SSID  "DESKTOP-8Q5E31L 8643"
// #define CONFIG_AP_SSID  "Hisilicon5"
#define CONFIG_AP_PWD   "12345678"

///< Configure the iot platform
/*Please modify the device id and pwd for your own */
#define CONFIG_DEVICE_ID  "60790e01ba4b2702c053ff03_helloMQTT" //设备ID：60790e01ba4b2702c053ff03_helloMQTT
#define CONFIG_DEVICE_PWD "hispark2021"    //华为云设备密码：hispark2021

#define CONFIG_USER_ID    "ERYO2ACJRVhi3861_mqtt;12010126;1R3OW;1670201249" 
#define CONFIG_USER_PWD   "96c8429d4b339628ab0aae219d6c8c575ce54ccc6a71ce0849e57002c62fa998;hmacsha256"

///< if you use the tls mode and x509mode, please modify the DEVICE CA AND PRIVATE KEY IN iot_main.c
// #define CONFIG_MQTT_SSL                  ///< which means use the tls
// #define CONFIG_MQTT_SSL_X509             ///< which means use the x509 mode, and must enable the SSL; if both disabled, it means use the tcp mode

#endif