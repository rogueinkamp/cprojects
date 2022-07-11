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

int main() {
   char string[50] = "192.168.100.0";
   char * bits;
   // Extract the first token
   char * network = strtok_r(string, "/", &bits);
   printf( " network %s\n", network ); //printing the token
   printf( " bits %s\n", bits ); //printing the token

   char ip[50] = "192.168.100.71";
    struct in_addr ip_addr;
    int ret = inet_aton(ip, &ip_addr);
    printf("----> %i", ret);
   return 0;
}
