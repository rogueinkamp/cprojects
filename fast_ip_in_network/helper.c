 #include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<ctype.h>

#include <stdbool.h>

struct NetworkAndMaskBits {
    char network_address[INET_ADDRSTRLEN];
    int mask_bits;
};


unsigned ip_in_network(const char* addr, const char* net) {
	struct in_addr ip_addr;
	int ret = inet_aton(addr, &ip_addr);
	if (!ret)
        printf("ret -> %i\n", ret);
		return false;
	char network[32];
	strncpy(network, net, strlen(net));

	char* slash = strstr(network, "/");
	if (!slash)
        printf("no slash\n");
		return false;
	int mask_len = atoi(slash + 1);

	*slash = '\0';
	struct in_addr net_addr;
	int ret2= inet_aton(network, &net_addr);
	if (!ret2)
        printf("ret -> %i\n", ret);
		return false;

	unsigned ip_bits = ip_addr.s_addr;
	unsigned net_bits = net_addr.s_addr;
	unsigned netmask = net_bits & ((1 << mask_len) - 1);
	unsigned res = (ip_bits & netmask) == net_bits;
    printf("RES -> %i", res);
    return res;
 }


struct NetworkAndMaskBits get_network_addr_and_mask_bits(const char *interface_ip_address_string) {
    // do stuff
    char ip_address_cidr_string[INET_ADDRSTRLEN];
    char *prefix;
    uint32_t prefix_int;
    uint32_t converted_ip_int;
    uint32_t network_bits;
    uint32_t shifted;
    struct in_addr ip_addr;
    struct NetworkAndMaskBits r;
	char ipNet[INET_ADDRSTRLEN];
	uint32_t ip_int;
	uint32_t netb;
	uint32_t mask_bits = 32;
    strcpy(ip_address_cidr_string, interface_ip_address_string);
    strtok_r(ip_address_cidr_string, "/", &prefix);
    sscanf(prefix, "%d", &prefix_int);
	inet_pton(AF_INET, ip_address_cidr_string, &ip_int);
	ip_int = ntohl(ip_int);
	/* printBits(ip_int); */
	unsigned long mask = (
		0xFFFFFFFF << (mask_bits - prefix_int)) & 0xFFFFFFFF;
	/* printBits(mask); */
	netb = ip_int & mask;
	netb = ntohl(netb);
	/* printBits(netb); */
	inet_ntop(
		AF_INET,
		&netb,
		ipNet,
		INET_ADDRSTRLEN
	);
    printf(
        "ORINGINAL: %s HOST_PORTION: '%s'  MASK_BITS: '%d' NETWORK_BITS: %d SHIFTED: %d, NETWORK_ADDRESS: %s\n",
        interface_ip_address_string,
        ip_address_cidr_string,
        prefix_int,
        network_bits,
        shifted,
        ipNet
    );
    r.mask_bits = mask_bits;
    strcpy(r.network_address, ipNet);
    return r;
}


int main() {
    char test_ip_cidr[INET_ADDRSTRLEN] = "192.168.0.71/27";
    char test_ip_network[INET_ADDRSTRLEN] = "192.168.0.64/27";
    struct NetworkAndMaskBits net_addr_and_mask = get_network_addr_and_mask_bits(test_ip_cidr);
    /* char mask_bits_char[100]; */
    /* sprintf(mask_bits_char, "%d", net_addr_and_mask.mask_bits); */
    unsigned _ip_in_network = ip_in_network(test_ip_cidr, net_addr_and_mask.network_address);
    printf("IN NETWORK %i", _ip_in_network);
    return 1;
}
