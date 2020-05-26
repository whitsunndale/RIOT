
#include <stdio.h>

#include "xtimer.h"
#include "stbm271.h"

#include "msg.h"
#include "net/ipv6/addr.h"
#include "net/gnrc.h"
#include "net/gnrc/netif.h"
#include "net/af.h"
#include "net/protnum.h"
#include "net/sock/udp.h"
#include "xtimer.h"
#include "board.h"

#define QUERY_MAX_SIZE 64

#if !defined(SERVER_ADDR)
#define SERVER_ADDR "fe80::9b95:29e9:e279:a5bd"
#endif // SERVER_ADDR
#if !defined(SERVER_PORT)
#define SERVER_PORT "8089"
#endif // SERVER_PORT

extern void udp_send(char *addr_str, char *port_str, char *data, size_t data_len, unsigned int num,
                 unsigned int delay);

int main(void)
{
    xtimer_sleep(10);

    printf("Available interfaces :\n");
    /* get interfaces and print their addresses */
    gnrc_netif_t *netif = NULL;
    char ifname[NETIF_NAMELENMAX];
    while ((netif = gnrc_netif_iter(netif))) {
        netif_get_name((netif_t *)netif, ifname);
        printf("Interface : %s\n", ifname);
        ipv6_addr_t ipv6_addrs[CONFIG_GNRC_NETIF_IPV6_ADDRS_NUMOF];
        int res = gnrc_netapi_get(netif->pid, NETOPT_IPV6_ADDR, 0, ipv6_addrs,
                                sizeof(ipv6_addrs));

        if (res < 0) {
            continue;
        }
        for (unsigned i = 0; i < (unsigned)(res / sizeof(ipv6_addr_t)); i++) {
            char ipv6_addr[IPV6_ADDR_MAX_STR_LEN];

            ipv6_addr_to_str(ipv6_addr, &ipv6_addrs[i], IPV6_ADDR_MAX_STR_LEN);
            printf("My address is %s\n", ipv6_addr);
        }
    }
    uint32_t delay = 1000000;

    puts("Starting air quality app\n");
    printf("Sending \"hello from RIOT\" to server\n");
    udp_send(SERVER_ADDR, "8080", "hello from RIOT", sizeof("hello from RIOT"), 1, delay);


    int low_ratio = 12345;

    stbm271_t dev;
    stbm271_params_t param = { .output1  = GPIO18,.output2 = GPIO19 };
    stbm271_init(&dev, &param);

    int i = 0;
    char query[QUERY_MAX_SIZE];

    // Main measurement/sending loop
    do {
        xtimer_sleep(30);
        if (i<2){
            printf("Skipping the first two measurements\n");
        } else {
        low_ratio = stbm271_read_output1(&dev);
        printf("Last low_ratio %d\n", low_ratio);
        sprintf(query, "air low_ratio=%d\n", low_ratio);
        udp_send(SERVER_ADDR, SERVER_PORT, query, strlen(query),1, delay);
        }
        i++;
    } while(1);

    /* main thread exits */
    return 0;
}
