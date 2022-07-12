#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<ctype.h>

#include <stdbool.h>

struct IPObject {
    char network_address[INET_ADDRSTRLEN];
    char host_address[INET_ADDRSTRLEN];
    int mask_bits;
};


// Check if the given IP address is in the specified network
unsigned ip_in_network(const char* address_to_check, const char* network_address, int mask_len, int debug) {
    // Let us ensure that we have a mask len
    if (!mask_len || mask_len == 0) {
        printf("NO_MASK_LEN: %i", mask_len);
        return 0;

    }
    int inet_aton_result;
    int _mask_len;

    char _addr_repr[INET_ADDRSTRLEN];
    snprintf(_addr_repr, INET_ADDRSTRLEN, "%s", address_to_check);
	struct in_addr _address_to_check;
	struct in_addr _network_address;

    if (debug == 1) {
        printf("INPUT | address_to_check=%s, network_address=%s, mask_len=%i\n", address_to_check, network_address, mask_len);
    }

    // Store the addr in as binary data so we can do bitwise on it
    // NOTE: that this will fail if addr is a cidr string
	inet_aton_result = inet_aton(address_to_check, &_address_to_check);
	if (!inet_aton_result) {
        printf("CONVERT_IP_TO_BINARY=False | inet_aton_ret_val=%i\n", inet_aton_result);
        return false;
    } else {
        printf("CONVERT_IP_TO_BINARY=True | inet_aton_ret_val=%i\n", inet_aton_result);
    }
	inet_aton_result = inet_aton(network_address, &_network_address);
	if (!inet_aton_result) {
        printf("CONVERT_NETWORK_IP_TO_BINARY=False | inet_aton_ret_val=%i\n", inet_aton_result);
        return false;
    } else {
        printf("CONVERT_NETWORK_IP_TO_BINARY=True | inet_aton_ret_val=%i\n", inet_aton_result);
    }
	uint32_t ip_bits = ntohl(_address_to_check.s_addr);
	uint32_t network_bits = ntohl(_network_address.s_addr);
	uint32_t mask = (0xFFFFFFFF << (32 - mask_len)) & 0xFFFFFFFF;
    uint32_t res = ((network_bits & mask) == (ip_bits & mask));
    if (debug == 1) {
        printf(
            "IN_NETWORK=%i | addr=%s network=%s, ip_bits=%i, net_bits=%i\n",
            res,
            _addr_repr,
            network_address,
            _address_to_check.s_addr,
            network_bits
        );
    }
    return res;
}


struct IPObject get_network_addr_and_mask_bits(const char *ip_addr_with_cidr) {
    // do stuff
    char ip_address_cidr_string[32];
    char host_address[32];
    char *prefix;
    uint32_t prefix_int;
    uint32_t converted_ip_int;
    uint32_t shifted;
    struct in_addr ip_addr;
    struct IPObject r;
	char network_address[32];
	uint32_t ip_int;
	uint32_t netb;
	uint32_t mask_bits = 32;

    strcpy(ip_address_cidr_string, ip_addr_with_cidr);

    // Split up the CIDR string where the prefix (mask bits) go to prefix var
    // ip_address_cidr_string is left with the host_address
    /* printf("ip_address_cidr_string: %s\n", ip_address_cidr_string); */
    strtok_r(ip_address_cidr_string, "/", &prefix);
    /* printf("ip_address_cidr_string after strtok_r: %s\n", ip_address_cidr_string); */

    // copy to own var as it ip_address_cidr_string no longer has cidr
	strcpy(host_address, ip_address_cidr_string);
    /* printf("host_address after strtok_r: %s\n", host_address); */
    sscanf(prefix, "%d", &prefix_int);
	inet_pton(AF_INET, ip_address_cidr_string, &ip_int);
	ip_int = ntohl(ip_int);
	/* printBits(ip_int); */
	uint32_t mask = (0xFFFFFFFF << (mask_bits - prefix_int)) & 0xFFFFFFFF;
	/* printBits(mask); */
	netb = ip_int & mask;
	netb = ntohl(netb);
	/* printBits(netb); */
	inet_ntop(
		AF_INET,
		&netb,
		network_address,
		INET_ADDRSTRLEN
	);
    printf(
        "ORIGINAL: %s HOST_PORTION: '%s' MASK_BITS: '%d' NETWORK_BITS: %d SHIFTED: %i, NETWORK_ADDRESS: %s\n",
        ip_addr_with_cidr,
        host_address,
        prefix_int,
        netb,
        mask,
        network_address
    );
    /* strcpy(r.host_address, host_address); */
    strcpy(r.network_address, network_address);
    r.mask_bits = prefix_int;
    return r;
}


int main() {
    int debug = 1;
    char test_network_1[32] = "192.168.0.64/27";
    char check_this_ip_1[INET_ADDRSTRLEN] = "192.168.0.71";
    struct IPObject ip_object = get_network_addr_and_mask_bits(test_network_1);
    unsigned _ip_in_network = ip_in_network(
        check_this_ip_1,
        ip_object.network_address,
        ip_object.mask_bits,
        debug
    );
    /* printf("IN NETWORK A %i\n", _ip_in_network); */
    char test_network_2[32] = "192.168.100.32/27";
    char check_this_ip_2[INET_ADDRSTRLEN] = "192.168.100.20";
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    struct IPObject ip_object_2 = get_network_addr_and_mask_bits(test_network_2);
    unsigned _ip_in_network_2 = ip_in_network(
        check_this_ip_2,
        ip_object_2.network_address,
        ip_object_2.mask_bits,
        debug
    );
    /* printf("IN NETWORK B %i\n", _ip_in_network_2); */
    return 1;
}
