#include <stdio.h>
#include "lwip/netifapi.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <hi_io.h>
#include <hi_gpio.h>
#include <hi_task.h>
#include <hi_watchdog.h>

#define INVAILD_SOCKET  (-1)

#define NATIVE_IP_ADDRESS       "192.168.3.88"
#define WECHAT_MSG_LIGHT_ON     "_light_on"
#define WECHAT_MSG_LIGHT_OFF    "_light_off"
#define DEVICE_MSG_LIGHT_ON     "device_light_on"
#define DEVICE_MSG_LIGHT_OFF    "device_light_off"
#define WECHAT_MSG_UNLOAD_PAGE  "UnoladPage"
#define RECV_DATA_FLAG_OTHER    (2)
#define HOST_PORT               (5566)
#define DEVICE_PORT             (6655)  

typedef void (*fn_msg_call_back)(hi_gpio_value val);

typedef struct function_callback{
    hi_bool  stop;
    hi_u32 conLost;
    hi_u32 queueID;
    hi_u32 iotTaskID;
    fn_msg_call_back    msg_call_back;
}function_callback;
function_callback gfn_callback;

void device_config_init(hi_gpio_value val)
{
    hi_io_set_func(HI_IO_NAME_GPIO_9, HI_IO_FUNC_GPIO_9_GPIO);
    hi_gpio_set_dir(HI_GPIO_IDX_9, HI_GPIO_DIR_OUT);
    hi_gpio_set_ouput_val(HI_GPIO_IDX_9, val);
}

int  DeviceMsgCallback(fn_msg_call_back msg_call_back)
{
    gfn_callback.msg_call_back = msg_call_back;
    return 0;
}

void wechatControlDeviceMsg(hi_gpio_value val)
{
    device_config_init(val);
}

int  udp_transport_init( struct sockaddr_in ser_addr, struct sockaddr_in remoteAddr)
{
    int s_server = socket(AF_INET, SOCK_DGRAM, 0);
    if (s_server == INVAILD_SOCKET) {
        printf("create server socket failed\r\n"); 
        close(s_server);
    }
    //本地主机ip和端口号
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(HOST_PORT);
    // ser_addr.sin_addr.s_addr = htons(INADDR_ANY);
    ser_addr.sin_addr.s_addr = inet_addr(NATIVE_IP_ADDRESS);
    if (bind(s_server, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1) {
        printf("bind socket failed\r\n");
        close(s_server);
    }
    //对方ip和端口号
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(DEVICE_PORT);
    ser_addr.sin_addr.s_addr = htons(INADDR_ANY);
    // remoteAddr.sin_addr.s_addr = inet_addr("192.168.3.88");

    return s_server;

}

int udp_server_demo(void)
{
    struct sockaddr_in ser_addr = {0};
    struct sockaddr_in remoteAddr;
    static int recv_data_flag = -1;
    char *send_data = NULL;
    int s_server;

    printf(" udp_server_demo\r\n");
    s_server = udp_transport_init(ser_addr, remoteAddr);

    while(1) {
        int addr_len = sizeof(remoteAddr);
        char recv_data[255] = {0};

        int recv_len = recvfrom(s_server, recv_data, 255, 0, (struct sockaddr*)&remoteAddr, (socklen_t*)&addr_len);
        if (recv_len) {
            printf("接收到一个连接:%s\r\n", inet_ntoa(remoteAddr.sin_addr));
            printf("接收到的数据：%s\r\n", recv_data);
            if(strstr(recv_data, WECHAT_MSG_LIGHT_OFF) != NULL) {
                printf("接收到控制设备信息：%s\r\n", recv_data);
                recv_data_flag = HI_FALSE;
                 wechatControlDeviceMsg(HI_GPIO_VALUE1);
            } else if (strstr(recv_data, WECHAT_MSG_LIGHT_ON) != NULL) {
                printf("接收到控制设备信息：%s\r\n", recv_data);
                recv_data_flag = HI_TRUE;
                wechatControlDeviceMsg(HI_GPIO_VALUE0);
            } else if (strstr(recv_data, WECHAT_MSG_UNLOAD_PAGE) != NULL) {
                printf("小程序退出当前界面\r\n");
                wechatControlDeviceMsg(HI_GPIO_VALUE1);
            } else {
                recv_data_flag = RECV_DATA_FLAG_OTHER;
            }
        }
        if (recv_data_flag == HI_TRUE) {
            send_data = DEVICE_MSG_LIGHT_ON;
            sendto(s_server, send_data, strlen(send_data), 0, (struct sockaddr*)&remoteAddr, addr_len);
        } else if(recv_data_flag == HI_FALSE) {
            send_data = DEVICE_MSG_LIGHT_OFF;
            sendto(s_server, send_data, strlen(send_data), 0, (struct sockaddr*)&remoteAddr, addr_len);
        } else if (recv_data_flag == RECV_DATA_FLAG_OTHER) {
            send_data = "收到来自服务端的消息";
            sendto(s_server, send_data, strlen(send_data), 0, (struct sockaddr*)&remoteAddr, addr_len);
        }
    }
    close(s_server);
    return NULL;
}


