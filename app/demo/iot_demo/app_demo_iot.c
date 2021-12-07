/*
 * Copyright (c) 2020 HiHope Community.
 * Description: IoT Platform
 * Author: HiSpark Product Team.
 * Create: 2020-5-20
 */

#include "iot_config.h"
#include "iot_log.h"
#include "iot_main.h"
#include "iot_profile.h"
#include <hi_task.h>
#include <string.h>
#include <hi_wifi_api.h>
#include <hi_mux.h>
#include <hi_io.h>
#include <hi_gpio.h>
#include <app_demo_pwm.h>
#include "hx711.h"
#include <app_demo_rtc.h>

/*attribute initiative to report */
#define TAKE_THE_INITIATIVE_TO_REPORT
/*oc request id*/
#define CN_COMMADN_INDEX                    "commands/request_id="
/* led test */
#define WECHAT_SUBSCRIBE_LIGHT               "light"
#define ON_STATE                             (1)
#define OFF_STATE                            (0)
#define WECHAT_SUBSCRIBE_LIGHT_OFF_STATE     "0"

/* cat food feed */
#define CAT_FEED_1                           "cat_feed_1"
#define CAT_FEED_2                           "cat_feed_2"
#define CAT_FEED_3                           "cat_feed_3"
#define CAT_FEED_4                           "cat_feed_4"
#define CAT_FEED_5                           "cat_feed_5"
/* dog food feed */
#define DOG_FEED_1                           "dog_feed_1"
#define DOG_FEED_2                           "dog_feed_2"
#define DOG_FEED_3                           "dog_feed_3"
#define DOG_FEED_4                           "dog_feed_4"
#define DOG_FEED_5                           "dog_feed_5"

// feed_cat_sum_piece 记录喂食总份数
int feed_cat_sum_piece=0;
int feed_dog_sum_piece=0;

// update 数据
int update_who=-1;
int update_piece=-1;
int update_flag=0;



int g_ligth_status = -1;

typedef void (*fn_msg_call_back)(hi_gpio_value val);

typedef struct function_callback{
    hi_bool  stop;
    hi_u32 conLost;
    hi_u32 queueID;
    hi_u32 iotTaskID;
    fn_msg_call_back    msg_call_back;
}function_callback;
function_callback g_functino_callback;


static void device_config_init(hi_gpio_value val)
{
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_9, HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_9, val);
}

static int  DeviceMsgCallback(fn_msg_call_back msg_call_back)
{
    g_functino_callback.msg_call_back = msg_call_back;
    return 0;
}

static void wechatControlDeviceMsg(hi_gpio_value val)
{
    device_config_init(val);
}


int feed_action(int dog_or_cat,int piece)
{

    //如果食物是满的，就不加了
    int full_cat_food_state= hx711_weight_2 > FULL_WEIGHT;
    int full_dog_food_state= hx711_weight > FULL_WEIGHT;
    
    if((dog_or_cat == CAT_H ||dog_or_cat == CAT_J) && full_cat_food_state)
        return 0;
    if((dog_or_cat == DOG) && full_dog_food_state)
        return 0;

    //更新投喂数据
    last_feed_who=dog_or_cat;
    if((dog_or_cat == DOG) ){
        last_feed_hour[1]=temp_hour;
        last_feed_minute[1]=temp_minute;
    }
    else if((dog_or_cat == CAT_H ||dog_or_cat == CAT_J) ){
        last_feed_hour[0]=temp_hour;
        last_feed_minute[0]=temp_minute;
    }
        
    //上报数据更新
    update_who=dog_or_cat;
    update_piece=piece;
    update_flag=1;


    if(dog_or_cat == CAT_H || dog_or_cat == CAT_J){
        
        feed_cat_sum_piece+=piece;
   
        for(int i=0;i<piece;i++){
            pwm_2_demo();
        }
    }
    else if(dog_or_cat == DOG){

        feed_dog_sum_piece+=piece;

        for(int i=0;i<piece;i++){
            pwm_3_demo();
        }
    }

}

///< this is the callback function, set to the mqtt, and if any messages come, it will be called
///< The payload here is the json string
static void DemoMsgRcvCallBack(int qos, const char *topic, const char *payload)
{
    // const char *requesID;
    // char *tmp;
    // IoTCmdResp_t resp;
    // WeChatProfile responseProfile;
    IOT_LOG_DEBUG("RCVMSG:QOS:%d TOPIC:%s PAYLOAD:%s\r\n",qos,topic, payload);
    /*app 下发的操作*/
    if (strstr(payload, WECHAT_SUBSCRIBE_LIGHT) != NULL) {
        if(strstr(payload, WECHAT_SUBSCRIBE_LIGHT_OFF_STATE) != NULL) {
            wechatControlDeviceMsg(HI_GPIO_VALUE1);
            g_ligth_status = HI_FALSE;
        } else {
            wechatControlDeviceMsg(HI_GPIO_VALUE0);
            g_ligth_status = HI_TRUE;
        }
    }
    else if (strstr(payload, CAT_FEED_1) != NULL) {
        printf("hey! 1 \n");
        if(qos==OFF_STATE){
            feed_action(CAT_H,1);
            printf("hey! 1 on \n");
        }
    }
    else if (strstr(payload, CAT_FEED_2) != NULL) {
        printf("hey! 2 \n");
        if(qos==OFF_STATE){
            feed_action(CAT_H,2);
            // pwm_2_demo();
            // //hi_sleep(10);
            // pwm_2_demo();
            printf("hey! 2 on \n");
        }
    }
    else if (strstr(payload, CAT_FEED_3) != NULL) {
        printf("hey! 3 \n");
        if(qos==OFF_STATE){
            feed_action(CAT_H,3);
            printf("hey! 3 on \n");
        }
    }
    else if (strstr(payload, CAT_FEED_4) != NULL) {
        printf("hey! 4 \n");
        if(qos==OFF_STATE){
            feed_action(CAT_H,4);
            printf("hey! 4 on \n");
        }
    }
    else if (strstr(payload, CAT_FEED_5) != NULL) {
        printf("hey! 5 \n");
        if(qos==OFF_STATE){
            feed_action(CAT_H,5);
            printf("hey! 5 on \n");
        }
    }
    /* DOG food feed */
    else if (strstr(payload, DOG_FEED_1) != NULL) {
        if(qos==OFF_STATE){
            feed_action(DOG,1);
            printf("hey! DOG 1 on \n");
        }
    }
    else if (strstr(payload, DOG_FEED_2) != NULL) {
        if(qos==OFF_STATE){
            feed_action(DOG,2);
            printf("hey! DOG 2 on \n");
        }
    }
    else if (strstr(payload, DOG_FEED_3) != NULL) {
        if(qos==OFF_STATE){
            feed_action(DOG,3);
            printf("hey! DOG 3 on \n");
        }
    }
    else if (strstr(payload, DOG_FEED_4) != NULL) {
        if(qos==OFF_STATE){
            feed_action(DOG,4);
            printf("hey! DOG 4 on \n");
        }
    }
    else if (strstr(payload, DOG_FEED_5) != NULL) {
        if(qos==OFF_STATE){
            feed_action(DOG,5);
            printf("hey! DOG 5 on \n");
        }
    }

    


    

    // tmp = strstr(topic,CN_COMMADN_INDEX);
    // if(tmp != NULL){
    //     ///< now you could deal your own works here --THE COMMAND FROM THE PLATFORM

    //         ///< now er roport the command execute result to the platform
    //         requesID = tmp + strlen(CN_COMMADN_INDEX);
    //         resp.requestID = requesID;
    //         resp.respName = NULL;
    //         resp.retCode = 0;   ////< which means 0 success and others failed
    //         resp.paras = NULL;
    //         // IOT_LOG_DEBUG("respose paras------------------------------ = %s\r\n", resp.paras);
    //         (void)IoTProfileCmdResp(CONFIG_DEVICE_PWD,&resp);
    // }
    return;
}

/*publish sample*/
hi_void iot_publish_sample(WeChatProfile weChatProfile)
{
    // WeChatProfile weChatProfile;

    // memset(&weChatProfile, 0, sizeof(weChatProfile));
    /*reported attribute*/
    weChatProfile.subscribeType = "type";
    weChatProfile.status.subState = "state";
    weChatProfile.status.subReport = "reported";
    weChatProfile.status.reportVersion = "version";
    weChatProfile.status.Token = "clientToken";
    /*report light*/
    if (g_ligth_status == HI_TRUE) {
        weChatProfile.reportAction.subDeviceAction_1 = "light";
        weChatProfile.reportAction.Action_1_num = 1;
    } else if (g_ligth_status == HI_FALSE){
        weChatProfile.reportAction.subDeviceAction_1 = "light";
        weChatProfile.reportAction.Action_1_num = 0;
    } else {
        weChatProfile.reportAction.subDeviceAction_1 = "light";
        weChatProfile.reportAction.Action_1_num = 0;
    }

    /*report  food*/
    weChatProfile.reportAction.subDeviceAction_2 = "cat_food";
    weChatProfile.reportAction.Action_2_num = (int)hx711_weight_2;
    /*report dog food*/
    weChatProfile.reportAction.subDeviceAction_3 = "dog_food";
    weChatProfile.reportAction.Action_3_num = (int)hx711_weight;

    /*report feed_cat_sum_piece*/
    weChatProfile.reportAction.subDeviceAction_4 = "feed_dog_sum_piece";
    weChatProfile.reportAction.Action_4_num = feed_dog_sum_piece;
    
    /*report feed_cat_sum_piece*/
    weChatProfile.reportAction.subDeviceAction_5 = "feed_cat_sum_piece";
    weChatProfile.reportAction.Action_5_num =  feed_cat_sum_piece;

    
    if(update_flag){
    // if(1){
        /*report feed time update*/
        weChatProfile.reportAction.subDeviceAction_6 = "date";
        weChatProfile.reportAction.Action_6_num = temp_date;
        weChatProfile.reportAction.subDeviceAction_7 = "hour";
        weChatProfile.reportAction.Action_7_num = temp_hour;
        weChatProfile.reportAction.subDeviceAction_8 = "minute";
        weChatProfile.reportAction.Action_8_num = temp_minute;
        /*report who and piece*/
        weChatProfile.reportAction.subDeviceAction_9 = "update_who";
        weChatProfile.reportAction.Action_9_num = update_who;
        weChatProfile.reportAction.subDeviceAction_10 = "update_piece";
        weChatProfile.reportAction.Action_10_num = update_piece;  
        update_flag=0;
    }
   
   // 喂食量上报
   if(have_eat_flag){
       /*report who and piece*/
        weChatProfile.reportAction.subDeviceAction_15 = "have_eat_who";
        weChatProfile.reportAction.Action_15_num = (int)have_eat_who;

        if( have_eat_weight < 0)
            have_eat_weight=-have_eat_weight;

        else if( have_eat_weight < 5 )
            have_eat_weight+=5;

        else if( have_eat_weight >20 )
            have_eat_weight-=5;

        else if(have_eat_weight > 40)
            have_eat_weight=30;


        weChatProfile.reportAction.subDeviceAction_16 = "have_eat_weight";
        weChatProfile.reportAction.Action_16_num = (int)have_eat_weight;  
        have_eat_flag=0;
   }

   
   

   if(temp_minute - last_check_minute > CHECK_TIME_MINUTE){//每 1min check一次

       //更新check时间
       last_check_minute=temp_minute;

       printf("check!!!\n\n\n\n");

       //长时间没看到就报警。测试时间是5min
       if( temp_minute - last_feed_minute[0] > WANGING_TIME_MINUTE ){
            warning_nsee_cat=1;    
       }else
       {
            warning_nsee_cat=0 ;    
       }
       
       if( temp_minute - last_feed_minute[1] > WANGING_TIME_MINUTE ){
            warning_nsee_dog=1;  
       }else
       {
            warning_nsee_dog=0;  
       }
       
       weChatProfile.reportAction.subDeviceAction_13 = "warning_nsee_cat";
       weChatProfile.reportAction.Action_13_num = warning_nsee_cat;
       weChatProfile.reportAction.subDeviceAction_14 = "warning_nsee_dog";
       weChatProfile.reportAction.Action_14_num = warning_nsee_dog;

   }
    



    //  weChatProfile.reportAction.subDeviceAction_3 = "temperature";
    // weChatProfile.reportAction.Action_3_num = (int)hx711_weight;
    // /*report humidity*/
    // weChatProfile.reportAction.subDeviceAction_4 = "humidity";
    // weChatProfile.reportAction.Action_4_num = (int)hx711_weight_2;
    /*report light_intensity*/
    

    IoTProfilePropertyReport(CONFIG_USER_ID, &weChatProfile);
}
///< this is the demo main task entry,here we will set the wifi/cjson/mqtt ready ,and 
///< wait if any work to do in the while
static hi_void *DemoEntry(hi_void *arg)
{
    WeChatProfile weChatProfile = {0};

    extern hi_void WifiStaReadyWait(hi_void);
    WifiStaReadyWait();

    extern void cJsonInit(void);
    cJsonInit();
    IoTMain();
    /*云端下发*/
    IoTSetMsgCallback(DemoMsgRcvCallBack);
    /*主动上报*/
#ifdef TAKE_THE_INITIATIVE_TO_REPORT
    while (1) {
        // hi_mux_pend(g_mux_id, HI_SYS_WAIT_FOREVER);
        ///< here you could add your own works here--we report the data to the IoTplatform
        ///< now we report the data to the iot platform
       // ///< here you could add your own works here--we report the data to the IoTplatform
       /*用户可以在这调用发布函数进行发布，需要用户自己写调用函数*/
       iot_publish_sample(weChatProfile);//发布例程
       hi_sleep(1000);
    }
#endif
    return NULL;
}

///< This is the demo entry, we create a task here, and all the works has been done in the demo_entry
#define CN_IOT_TASK_STACKSIZE  0x1000   
#define CN_IOT_TASK_PRIOR 25
#define CN_IOT_TASK_NAME "IOTDEMO"
int app_demo_iot(void)
{
    hi_u32 ret;
    hi_task_attr attr = {0};
    hi_u32 taskID;

    attr.stack_size = CN_IOT_TASK_STACKSIZE;
    attr.task_prio = CN_IOT_TASK_PRIOR;
    attr.task_name = CN_IOT_TASK_NAME;
    ret = hi_task_create(&taskID, &attr, DemoEntry, NULL);
    if (ret != HI_ERR_SUCCESS) {
       IOT_LOG_ERROR("IOT TASK CTREATE FAILED");
    }
    return 0;
}
