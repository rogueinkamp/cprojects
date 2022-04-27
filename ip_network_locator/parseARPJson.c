#include <stdint.h>
#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <arpa/inet.h>
#include <string.h>
#include <inttypes.h>

struct NetworkAndMaskBits {
    char network_address[INET_ADDRSTRLEN];
    int mask_bits;
};

struct NetworkToMask {
    char network_address[INET_ADDRSTRLEN];
    int mask_bits;
};

void showbits(unsigned int x) {
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}


struct NetworkAndMaskBits get_network_addr_and_mask_bits(const char *interface_ip_address_string) {
    // do stuff
    char ip_address_cidr_string[INET_ADDRSTRLEN];
    char *prefix;
    uint32_t prefix_int;
    uint32_t converted_ip_int;
    uint32_t network_bits;
    uint32_t shifted;
    int network_address_binary;
    struct in_addr ip_addr;
    struct NetworkAndMaskBits r;
    /* struct sockaddr_in sa; */
	/* char ip[INET_ADDRSTRLEN] = "192.168.1.67"; */
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
    /* [
        {
            "address": "thu",
            "age": "apr",
            "hardwareaddr": "14",
            "state": "20:15:15.310",
            "type": "utc"
    }, */
    json_object *arp_root = json_object_from_file("./arp_struct.json");

    /*
    [
        {
            "id": 49863,
            "address": "10.164.255.24",
            "description": "",
            "assigned_object_id": 375916
        },
    */
    json_object *device_networks_root = json_object_from_file("./device_networks.json");

    if (!arp_root) {
        printf("No file 'arp_struct.json' in current dir check to make sure\n");
        return 1;
    }
    if (!device_networks_root) {
        printf("No file 'device_networks.json' in current dir check to make sure\n");
        return 1;
    }
    int arp_root_count = json_object_array_length(arp_root);
    int device_networks_root_count = json_object_array_length(device_networks_root);

    for (int i = 0; i < arp_root_count; i++) {
        json_object *element = json_object_array_get_idx(arp_root, i);
        json_object *address = json_object_object_get(element, "Address");

        const char *address_str = json_object_get_string(address);
        uint32_t converted_ip_int;

        char str[INET_ADDRSTRLEN];

        // store this IP address in converted_ip_int:
        inet_pton(AF_INET, address_str, &converted_ip_int);

        /* printf("JSON_ADDRESS: %s | CONVERTED_INT=%i\n", address_str, converted_ip_int); */
        for (int j = 0; j < device_networks_root_count; j++) {
            json_object *device_element = json_object_array_get_idx(device_networks_root, j);
            json_object *device_address = json_object_object_get(device_element, "address");
            const char *interface_ip_address_string = json_object_get_string(device_address);

            char ensure_chars[] = "/";
            // Ensure that there is a / in the ip network string or this wont work
            int valid = 0;
            for (int i = 0; i < strlen(interface_ip_address_string) && !(valid == 1); i++) {
                char * pch;
                pch = strchr(ensure_chars, interface_ip_address_string[i]);
                if (pch != NULL) {
                    valid = 1;
                }
            }

            /* printf("ok2\n"); */
            struct NetworkAndMaskBits ret_struct;
            if (valid == 1) {
                /* printf("ok3\n"); */
                ret_struct = get_network_addr_and_mask_bits(interface_ip_address_string);
            } else {
                /* printf("nok3\n"); */
                printf("INVALID: %s\n", interface_ip_address_string);
            }

            /* printf("Network Address: %s | Mask_Bits: %d\n", ret_struct.network_address, ret_struct.mask_bits); */
        }
    }
    return 0;
}
