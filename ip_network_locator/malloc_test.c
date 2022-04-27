#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <arpa/inet.h>
#include <string.h>
#include <inttypes.h>


int main() {
    char ip_base[INET_ADDRSTRLEN];
    char *ptr = (char* )malloc(sizeof(ip_base) * 2);
    strcpy(&ptr[0], "192.168.100.1");
    for (int i = 0; i < *ptr; i++) {
        printf("%c", ptr[i]);
    }
    free(ptr);

    /* struct Student { */
    /*     int rollnumber; */
    /*     char studentname[10]; */
    /*     float percentage; */
    /* }; */
    /* struct Student studentRecord[5]; */

    return 0;
}
