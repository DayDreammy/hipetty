#include <stdio.h>
#include <string.h>
#include "lwip/netifapi.h"
#include "lwip/apps/mdns.h"

extern void mdns_resp_demo(void);

void lwip_mdns_demo(void)
{
    mdns_resp_demo();
}



