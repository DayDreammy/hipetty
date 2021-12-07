#include <stdio.h> 
#include "lwip/netifapi.h"
#include <string.h> 
#include <errno.h> 
#include <stdlib.h> 
#define STACK_IP "192.168.3.85" 
#define STACK_PORT 2277 
#define PEER_PORT 3377 
#define PEER_IP "192.168.3.78" 
#define MSG "Hi, I am lwIP" 
#define BUF_SIZE (1024 * 8) 
typedef unsigned char u8_t; 
typedef signed int s32_t; 
u8_t g_buf[BUF_SIZE+1] = {0}; 
/* Global variable for lwIP Network interface */ 
int sample_tcp_server() 
{
    s32_t sfd = -1;
    s32_t lsfd = -1; 
    struct sockaddr_in srv_addr = {0}; 
    struct sockaddr_in cln_addr = {0}; 
    socklen_t cln_addr_len = sizeof(cln_addr); 
    s32_t ret = 0, i = 0; 
 /* tcp server */ 
    printf("going to call socket\n"); 
    lsfd = socket(AF_INET,SOCK_STREAM,0); 
    if (lsfd == -1) {
        printf("socket failed, return is %d\n", lsfd); 
        goto FAILURE; 
    } 
    printf("socket succeeded\n"); 
    srv_addr.sin_family = AF_INET; 
    srv_addr.sin_addr.s_addr = inet_addr(STACK_IP); 
    srv_addr.sin_port = htons(STACK_PORT); 
    ret = bind(lsfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
    for (int i = 0; i < sizeof(srv_addr.sin_addr.s_addr); i++) {
        printf("srv_addr.sin_addr.s_addr:%ds\n", srv_addr.sin_addr.s_addr);
    }
    printf("lsfd:%d, srv_addr.sin_family:%d,srv_addr.sin_port:%d\n", lsfd,srv_addr.sin_family,srv_addr.sin_port);
    if (ret != 0) {
        printf("bind failed, return is %d\n", ret);
        goto FAILURE; 
    } 
    ret = listen(lsfd, 0); 
    if (ret != 0) {
        printf("listen failed, return is %d\n", ret);
        goto FAILURE; 
    } 
    printf("listen succeeded, return is %d\n", ret);
    printf("going to call accept\n"); 
    sfd = accept(lsfd, (struct sockaddr *)&cln_addr, &cln_addr_len); 
    if (sfd < 0) {
        printf("accept failed, return is %d\n", sfd);    
    } 
    printf("accept succeeded, return is %d\n", sfd);
 /* tcp server */ 
 /* send */ 
    memset(g_buf, 0, BUF_SIZE); 
    strcpy(g_buf, MSG); 
    printf("calling send...\n"); 
    ret = send(sfd, g_buf, sizeof(MSG), 0); 
    if (ret <= 0) {
        printf("send failed, return is %d, i is %d\n", ret, i); 
        goto FAILURE; 
    } 
    printf("send fin²ä¯ ret is %d\n", ret); 
    /* send */ 
    /* recv */ 
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
    close(lsfd); 
    return 0; 
FAILURE: 
    close(sfd); 
    close(lsfd); 
    printf("errno is %d\n", errno); 
    return -1; 
} 

