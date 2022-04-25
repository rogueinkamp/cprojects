#include <stdint.h>
#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <arpa/inet.h>


int main() {
    json_object *device_networks_root = json_object_from_file("./device_networks.json");
    json_object *arp_root = json_object_from_file("./arp_struct.json");
    if (!arp_root) {
        printf("No file 'arp_struct.json' in current dir check to make sure\n");
        return 1;
    }
    if (!device_networks_root) {
        printf("No file 'device_networks.json' in current dir check to make sure\n");
        return 1;
    }
    int root_count = json_object_array_length(arp_root);
    for (int i = 0; i < root_count; i++) {
        json_object *element = json_object_array_get_idx(arp_root, i);
        json_object *address = json_object_object_get(element, "Address");

        const char *address_str = json_object_get_string(address);
        uint32_t converted_ip_int;

        char str[INET_ADDRSTRLEN];

        // store this IP address in converted_ip_int:
        inet_pton(AF_INET, address_str, &converted_ip_int);

        printf("JSON_ADDRESS: %s | CONVERTED_INT=%i\n", address_str, converted_ip_int);
    };
    return 0;
}
