#include <stdio.h>
#include "lwip/netifapi.h"
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#define CLIENT_SOCKET_CREATE_FAILED (-1)

int udp_client_demo(void)
{
    struct sockaddr_in sin = {0};
    struct sockaddr_in server_addr = {0};
    int ret = -1;
    /*create socket*/
    int s_client = socket(AF_INET, SOCK_DGRAM, 0);
    if (s_client == CLIENT_SOCKET_CREATE_FAILED) {
        printf("create socket Fialed\r\n");
        goto UDP_CLIENT_FAILURE;
    }
    //本地主机ip和端口号
    sin.sin_family = AF_INET;
    sin.sin_port = htons(6655);
    sin.sin_addr.s_addr = inet_addr("192.168.3.88");
    ret = bind(s_client, (struct sockaddr*)&sin, sizeof(sin));
    if (ret < 0) {
        printf("client bind failed %d, %s\r\n", __LINE__, errno);
    }
    //对方ip和端口号
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5566);
    server_addr.sin_addr.s_addr = inet_addr("192.168.3.99");

    int len = sizeof(sin);
    char *send_data = "这是客户端的消息\r\n";
    while(1) {
        // sendto(s_client, send_data, strlen(send_data), 0 ,(struct sockaddr*)&sin, len);
        sendto(s_client, send_data, strlen(send_data), 0 ,(struct sockaddr*)&server_addr, len);
        char recv_data[255] = {0};
        // int recv_len = recvfrom(s_client, recv_data, 255, 0, (struct sockaddr*)&sin, &len);
        int recv_len = recvfrom(s_client, recv_data, 255, 0, (struct sockaddr*)&server_addr, &len);
        if (recv_len) {
            printf("recv_data = %s\r\n", recv_data);
        }

    }
    close(s_client);
    return 0;

UDP_CLIENT_FAILURE:
    close(s_client);
    return CLIENT_SOCKET_CREATE_FAILED;
}
