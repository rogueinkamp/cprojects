 #include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include<ctype.h>

#include <stdbool.h>


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


bool fast_ip_in_network(char ip[INET_ADDRSTRLEN], char ip_cidr[INET_ADDRSTRLEN], uint32_t prefix, char* network_address, uint32_t mask_bits) {
	uint32_t ip_int;
	uint32_t netb;
	uint32_t MASK_TOTAL_BITS = 32;
	inet_pton(AF_INET, ip, &ip_int);
	ip_int = ntohl(ip_int);
	unsigned long mask = (
		0xFFFFFFFF << (MASK_TOTAL_BITS - mask_bits)) & 0xFFFFFFFF;
	netb = ip_int & mask;
	netb = ntohl(netb);
	inet_ntop(
		AF_INET,
		&netb,
		ip_cidr,
		INET_ADDRSTRLEN
	);
	printf(
		"network for %s and mask %d: %s",
		ip,
		prefix,
		ip_cidr
	);
    return ip_in_network(ip_cidr, prefix);
}


int main() {
    return 0;
}
