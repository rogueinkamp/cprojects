#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	struct json_object *parsed_json;
	struct json_object *address;
	struct json_object *age;
	struct json_object *hardware_address;
	struct json_object *state;
	struct json_object *type;

    struct json_object arpObjects[5];
	size_t n_arp;

	size_t i;	

	fp = fopen("test.json","r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
	char buffer[size];
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "address", &address);
	json_object_object_get_ex(parsed_json, "age", &age);
	json_object_object_get_ex(parsed_json, "hardware_address", &hardware_address);
	json_object_object_get_ex(parsed_json, "state", &state);
	json_object_object_get_ex(parsed_json, "type", &type);

	printf("Name: %s\n", json_object_get_string(address));
	printf("Age: %d\n", json_object_get_int(hardware_address));

	n_arp = json_object_array_length(parsed_json);
	printf("Found %lu friends\n", n_arp);

	for(i=0; i < n_arp; i++) {
		arp = json_object_array_get_idx(parsed_json, i);
		printf("%lu. %s\n", i+1, json_object_get_string(arp));
	}	
}
