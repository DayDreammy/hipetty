#include <stdio.h> 
#include "lwip/netifapi.h"
#include <string.h> 
#include <errno.h> 
#include <stdlib.h> 

#define STACK_IP "192.168.3.78" 
#define STACK_PORT 3377 
#define PEER_PORT 2277 
#define PEER_IP "192.168.3.85" 
#define MSG "Hi, I am lwIP" 
#define BUF_SIZE (1024 * 8) 
typedef unsigned char u8_t; 
typedef signed int s32_t; 
u8_t g_buf[BUF_SIZE + 1] = {0}; 
/* Global variable for lwIP Network interface */ 
int sample_tcp_client() 
{
    s32_t sfd = -1; 
    struct sockaddr_in srv_addr = {0}; 
    struct sockaddr_in cln_addr = {0}; 
    socklen_t cln_addr_len = sizeof(cln_addr); 
    s32_t ret = 0, i = 0; 
 /* tcp client connection */ 
    printf("going to call socket\n"); 
    sfd = socket(AF_INET,SOCK_STREAM,0); 
    if (sfd == -1) {
        printf("socket failed, return is %d\n", sfd); 
        goto FAILURE; 
    } 
    printf("socket succeeded, sfd %d\n", sfd);
    srv_addr.sin_family = AF_INET; 
    srv_addr.sin_addr.s_addr = inet_addr(PEER_IP); 
    srv_addr.sin_port = htons(PEER_PORT); 
    printf("going to call connect\n"); 
    ret = connect(sfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)); 
    if (ret != 0) {
        printf("connect failed, return is %d\n", ret); 
        goto FAILURE; 
    } 
    printf("connec succeeded, return is %d\n", ret);
    /* tcp client connection */ 
    /* send */ 
    memset(g_buf, 0, BUF_SIZE); 
    strcpy(g_buf, MSG); 
    printf("calling send...\n"); 
    ret = send(sfd, g_buf, sizeof(MSG), 0); 
    if (ret <= 0) {
    printf("send failed, return is %d,i is %d\n", ret, i); 
    goto FAILURE; 
 } 
    printf("send finish ret is %d\n", ret); 
    /* send */ 
    /* recv */ 
    memset(g_buf, 0, BUF_SIZE); 
    printf("going to call recv\n"); 
    ret = recv(sfd, g_buf, sizeof(g_buf), 0);
    memset(g_buf, 0, BUF_SIZE); 
    printf("going to call recv\n"); 
    ret = recv(sfd, g_buf, sizeof(g_buf), 0); 
    if (ret <= 0) {
        printf("recv failed, return is %d\n", ret); 
        goto FAILURE; 
    } 
    printf("recv succeeded, return is %d\n", ret); 
    printf("received msg is : %s\n", g_buf); 
 /* recv */ 
    close(sfd); 
    return 0; 
FAILURE: 
    close(sfd); 
    printf("errno is %d\n", errno); 
    return -1; 
} 
