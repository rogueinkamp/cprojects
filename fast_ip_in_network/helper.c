 #include <netinet/in.h>
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


/*

addr is the IP address to check as single IP not in CIDR format
net is the Network IP address

*/
unsigned ip_in_network(const char* addr, const char* net, int mask_len) {
    addr = "192.168.0.71";
    net = "192.168.0.64";
    mask_len = 27;
    char _addr_repr[INET_ADDRSTRLEN];
    /* strncpy(_addr_repr, addr, strlen(addr)); */
    snprintf(_addr_repr, INET_ADDRSTRLEN, "%s", addr);
    /* printf("addr=%s _addr_repr=%s\n", addr, _addr_repr); */
    int _mask_len;
	char network[32];
	struct in_addr ip_addr;

    printf("input | addr=%s, net=%s, mask_len=%i\n", addr, net, mask_len);
	int ret = inet_aton(addr, &ip_addr);
    printf("ret -> %i\n", ret);
	if (!ret) {
	        printf("ret -> %i\n", ret);
            return false;
    }
	strncpy(network, net, strlen(net));
    char * bits;
    char * char_addr = (char*)addr;
    /* printf("char_addr=%s\n", char_addr );  */
    char * _network = strtok_r(char_addr, "/", &bits);
    printf("NETWORK=%s BITS=%s\n", _network, bits);

	if (bits) {
        printf(
            "CHECK_IP_ADDRESS_CIDR | CIDR=True | addr=%s set mask_len to input of function %s\n",
            _addr_repr,
            bits
        );
        int _mask_len = atoi(bits);
    } else {
        printf(
            "CHECK_IP_ADDR_CIDR | CIDR=False | addr=%s set mask_len to int of network bits of cidr portion of addr %s\n",
            _addr_repr,
            bits
        );
        _mask_len = mask_len;
    }

    printf("_mask_len = %i\n", _mask_len);

	struct in_addr net_addr;
	int ret2= inet_aton(network, &net_addr);
	/* if (!ret2) */
	/*         printf("ret -> %i\n", ret); */
	/* 	return false; */

	unsigned ip_bits = ip_addr.s_addr;
	unsigned net_bits = net_addr.s_addr;
    unsigned res = ((net_bits & _mask_len) == (ip_bits & _mask_len));
    printf("IN_NETWORK=%i | addr=%s network=%s, ip_bits=%i, net_bits=%i\n", res, _addr_repr, net, ip_bits, net_bits);
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
        "ORIGINAL: %s HOST_PORTION: '%s' MASK_BITS: '%d' NETWORK_BITS: %d SHIFTED: %d, NETWORK_ADDRESS: %s\n",
        interface_ip_address_string,
        ip_address_cidr_string,
        prefix_int,
        network_bits,
        shifted,
        ipNet
    );
    r.mask_bits = prefix_int;
    strcpy(r.network_address, ipNet);
    return r;
}


int main() {
    char test_ip_cidr[INET_ADDRSTRLEN] = "192.168.0.22/27";
    char test_ip_network[INET_ADDRSTRLEN] = "192.168.0.64/27";
    struct NetworkAndMaskBits net_addr_and_mask = get_network_addr_and_mask_bits(test_ip_cidr);
    /* char mask_bits_char[100]; */
    /* sprintf(mask_bits_char, "%d", net_addr_and_mask.mask_bits); */
    unsigned _ip_in_network = ip_in_network(
        test_ip_cidr,
        net_addr_and_mask.network_address,
        net_addr_and_mask.mask_bits
    );
    printf("IN NETWORK %i\n", _ip_in_network);
    return 1;
}
