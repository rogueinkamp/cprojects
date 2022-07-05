 #include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<ctype.h>

#include <stdbool.h>

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

enum cardinal_points { north = 0, east = 90, south = 180, west = 270 };


int len(char* s){
	int len;
	len = strlen(s);
	return len;
}

int doNothingImportant(void){
	printf("did nothing important\n");
	return 1;
}

bool ip_in_network(const char* addr, const char* net) {
	struct in_addr ip_addr;
	int ret = inet_aton(addr, &ip_addr);
	if (!ret)
		return false;
	char network[32];
	strncpy(network, net, strlen(net));

	char* slash = strstr(network, "/");
	if (!slash)
		return false;
	int mask_len = atoi(slash + 1);

	*slash = '\0';
	struct in_addr net_addr;
	int ret2= inet_aton(network, &net_addr);
	if (!ret2)
		return false;

	unsigned ip_bits = ip_addr.s_addr;
	unsigned net_bits = net_addr.s_addr;
	unsigned netmask = net_bits & ((1 << mask_len) - 1);
	return (ip_bits & netmask) == net_bits;
 }


int stohi(char *ip){
	char c;
	c = *ip;
	unsigned int integer;
	int val;
	int i,j=0;
	for (j=0;j<4;j++) {
		if (!isdigit(c)){  //first char is 0
			return (0);
		}
		val=0;
		for (i=0;i<3;i++) {
			if (isdigit(c)) {
				val = (val * 10) + (c - '0');
				c = *++ip;
			} else
				break;
		}
		if(val<0 || val>255){
			return (0);	
		}	
		if (c == '.') {
			integer=(integer<<8) | val;
			c = *++ip;
		} 
		else if(j==3 && c == '\0'){
			integer=(integer<<8) | val;
			break;
		}
			
	}
	if(c != '\0'){
		return (0);	
	}
	return (htonl(integer));
}

char* IPIntToString(int ip){
  static char result[64];

  sprintf(result, "%d.%d.%d.%d",
    (ip >> 24) & 0xFF,
    (ip >> 16) & 0xFF,
    (ip >>  8) & 0xFF,
    (ip      ) & 0xFF);

  return result;
}

void printBits(int val){
    for(unsigned int mask = 0x80000000; mask; mask >>= 1){
         printf("%d", !!(mask & val));
    }
	printf("\n");
}

void convertStuff() {
	char ip[INET_ADDRSTRLEN] = "192.168.1.67";
	char ipNet[INET_ADDRSTRLEN];
	uint32_t ip_int;
	uint32_t netb;
	uint32_t mask_bits = 32;
	uint32_t prefix = 27;
	
	inet_pton(AF_INET, ip, &ip_int);
	ip_int = ntohl(ip_int);
	printBits(ip_int);
	unsigned long mask = (
		0xFFFFFFFF << (mask_bits - prefix)) & 		0xFFFFFFFF;
	printBits(mask);
	netb = ip_int & mask;
	netb = ntohl(netb);
	printBits(netb);
	inet_ntop(
		AF_INET,
		&netb,
		ipNet,
		INET_ADDRSTRLEN
	);
	printf(
		"network for %s and mask %d: %s",
		ip,
		prefix,
		ipNet
	);

}

int main(){
	struct test {
		char name[1000];
		unsigned int ERRCODE;
		//unsigned int len;
	}; 
	int testCollectLen = 0;
	struct test testCollect[10];
	testCollect[0].ERRCODE = 999;
	strcpy(testCollect[0].name, "test name");
	testCollectLen++;
	
	
	//int *tcp = testCollect;
	for (int i = 0; i < testCollectLen; i++){
		// if (!&testCollect[i].name == "")
	
		printf("%s - %d\n", testCollect[i].name,
		testCollect[i].ERRCODE);
	}

	char s[] = "hello";
	printf("len of hello is %i\n", len(s));
	printf("west enum value: %d\n", west);
	doNothingImportant();
	convertStuff();
	return 0;

}
