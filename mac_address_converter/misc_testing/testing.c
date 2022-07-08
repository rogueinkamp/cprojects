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


#include<stdio.h>
#include <string.h>

int main() {
   char string[50] = "192.168.100.0";
   char * bits;
   // Extract the first token
   char * network = strtok_r(string, "/", &bits);
   printf( " network %s\n", network ); //printing the token
   printf( " bits %s\n", bits ); //printing the token
   return 0;
}


    char * bits;
    char * char_addr = (char*)addr;
    printf("char_Addr=%s\n", char_addr ); //printing the token
    char * _network = strtok_r(char_addr, "/", &bits);
    printf("NETWORK=%s BITS=%s\n", _network, bits);

	if (!bits) {
        printf(
            "CHECK_IP_ADDRESS_CIDR | CIDR=True | addr=%s set mask_len to input of function %s\n",
            addr,
            bits
        );
        int _mask_len = atoi(bits + 1);
        /* _mask_len = mask_len; */
        char _network[32];
        strncpy(_network, addr, strlen(net));
        /* printf( " network %s\n", network ); */
    } else {
        printf(
            "CHECK_IP_ADDR_CIDR | CIDR=False | addr=%s set mask_len to int of network bits of cidr portion of addr %s\n",
            addr,
            bits
        );
        /* *slash = '\0'; */
    }
        int _mask_len = atoi(_network);


