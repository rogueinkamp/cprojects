#include <stdint.h>
#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <arpa/inet.h>
#include <string.h>

struct NetworkAndMaskBits {
    char network_address[200];
    int mask_bits;
};

void showbits(unsigned int x )
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}


struct NetworkAndMaskBits get_network_addr_and_mask_bits(const char *interface_ip_address_string) {
    // do stuff
    char ip_address_cidr_string[200];
    char *mask_bits;
    uint32_t mask_bits_int;
    uint32_t converted_ip_int;
    uint32_t network_bits;
    uint32_t shifted;
    int network_address_binary;
    struct in_addr ip_addr;
    struct NetworkAndMaskBits r;
    struct sockaddr_in sa;
    /* char str[INET_ADDRSTRLEN]; */

   char network_address[16];


    strcpy(ip_address_cidr_string, interface_ip_address_string);
    strtok_r(ip_address_cidr_string, "/", &mask_bits);

    sscanf(mask_bits, "%d", &mask_bits_int);

    // store this IP address in sa:
    inet_pton(AF_INET, ip_address_cidr_string, &(sa.sin_addr));
    converted_ip_int = sa.sin_addr.s_addr;

    /* strcpy(r.network_address, ip_address_cidr_string); */

    /* showbits(converted_ip_int); */
    shifted = ((0xFFFFFFFFF << (32 - mask_bits_int)) & 0xFFFFFFFFF);
    showbits(shifted);
    network_address_binary = (sa.sin_addr.s_addr & shifted);
    showbits(network_address_binary);

    /* src.sin_addr.s_addr = network_address_binary; */
    /* char *network_address = inet_ntoa(ip_addr); */

    sa.sin_addr.s_addr=network_address_binary;
    inet_ntop(AF_INET, &sa.sin_addr, network_address, INET_ADDRSTRLEN);
    showbits(network_address_binary);
    /* inet_ntop(AF_INET, &network_address_binary, network_address, INET_ADDRSTRLEN); */

   /* char network_address[16]; */
   /* unsigned char bytes[4]; */
   /* int i; */
   /* for(i=0; i<4; i++) { */
   /*    bytes[i] = (network_address_binary >> i*8) & 0xFF; */
   /* } */
   /*  sprintf(network_address, "%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]); */
    printf(
        "ORINGINAL: %s HOST_PORTION: '%s'  MASK_BITS: '%d' NETWORK_BITS: %d SHIFTED: %d, NETWORK_ADDRESS: %s\n",
        interface_ip_address_string,
        ip_address_cidr_string,
        mask_bits_int,
        network_bits,
        shifted,
        network_address
    );

    /* r.mask= 10; */
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
            /* char network_address[12]; */
            /* uint32_t mask_bits; */
            json_object *device_element = json_object_array_get_idx(device_networks_root, j);
            json_object *device_address = json_object_object_get(device_element, "address");
            const char *interface_ip_address_string = json_object_get_string(device_address);
            /* printf("NETWORK_FROM_DEVICE: %s\n", interface_ip_address_string); */

            struct NetworkAndMaskBits ret_struct;
            ret_struct = get_network_addr_and_mask_bits(interface_ip_address_string);
            /* printf("Network Address: %s | Mask_Bits: %d\n", ret_struct.network_address, ret_struct.mask_bits); */
        };
    };
    return 0;
}
