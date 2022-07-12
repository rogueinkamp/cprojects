/* #include<stdio.h> */
/* #include<string.h> */

/* int main() { */
/*     int a = -4; */
/*     printf("Here is your signed int %i\n", a); */

/*     unsigned b = -4; */
/*     printf("Here is your usigned int %i\n", b); */

/*     char network[100] = "192.168.100.0/27"; */
/* 	char * slash = strtok(network, "//"); */
/*     printf("network=%s slash=%s\n", network, slash); */
/*     return 0; */
/* } */


#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<ctype.h>

#include <stdbool.h>


#include<stdio.h>
#include <string.h>

bool ip_in_network(const char* addr, const char* net) {
    struct in_addr ip_addr;
    if (!inet_aton(addr, &ip_addr)) return false;

    char network[32];
    strncpy(network, net, strlen(net));

    char* slash = strstr(network, "/");
    if (!slash) return false;
    int mask_len = atoi(slash + 1);

    /* *slash = "\0"; */
    struct in_addr net_addr;
    if (!inet_aton(network, &net_addr)) return false;

    unsigned ip_bits = ip_addr.s_addr;
    unsigned net_bits = net_addr.s_addr;
    unsigned netmask = net_bits & ((32 << mask_len) - 1); return (ip_bits & netmask) == net_bits;
}
void printBits(int val){
    for(unsigned int mask = 0x80000000; mask; mask >>= 1){
         printf("%d", !!(mask & val));
    }
	printf("\n");
}
int main() {
   /* char string[INET_ADDRSTRLEN] = "192.168.100.0"; */
   /* char * bits; */
   /* // Extract the first token */
   /* char * network = strtok_r(string, "/", &bits); */
   /* printf( " network %s\n", network ); //printing the token */
   /* printf( " bits %s\n", bits ); //printing the token */
    int ret;

    char ip_to_eval[INET_ADDRSTRLEN] = "192.168.0.71";
    struct in_addr ip_to_eval_struct;
    ret = inet_aton(ip_to_eval, &ip_to_eval_struct);


    char network_to_check[INET_ADDRSTRLEN] = "192.168.0.64";
    /* char network[32]; */
    /* strncpy(network, network_to_check, strlen(network_to_check)); */

    /* char* slash = strstr(network, "/"); */
    /* if (!slash) return false; */
    /* int mask_len = atoi(slash + 1); */
    int mask_len = 27;
    /* printf("network_to_check %s mask_len: %i\n", network_to_check, mask_len); */

    /* *slash = "\0"; */
    struct in_addr network_to_check_struct;
    ret = inet_aton(network_to_check, &network_to_check_struct);

    uint32_t ip_bits = ntohl(ip_to_eval_struct.s_addr);
    uint32_t network_bits = ntohl(network_to_check_struct.s_addr);
    /* uint32_t mask = network_bits & ((1 << mask_len) - 1); */
    uint32_t mask = (0xFFFFFFFF << (32 - mask_len)) & 0xFFFFFFFF;
    printBits(ip_bits);
    printBits(mask);
    printBits(ip_bits & mask);
    printf("+++++++++++++++++++++++++++++++++++++\n");
    printBits(network_bits);
    printBits(mask);
    printBits(network_bits & mask);
    ret = (ip_bits & mask) == (network_bits & mask);
    /* ret = ip_in_network(ip_to_eval, network_to_check); */
    printf("ret -> %i\n", ret);
    if (ret == 1) {
        printf("yes\n");
    } else {
        printf("No\n");
    }
   return 0;
}
