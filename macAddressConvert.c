#include<stdio.h>
#include<string.h>
#include <limits.h>
#include <ctype.h>

static char lastStr[20] = "";


char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

const char* convert_mac_addr_str_std_fmt(char *maybeMacAddress) {
    char* s;
    char *badChar[6] = {"[", ".", ":", "-", "]", " "};
    int strLen = strlen(maybeMacAddress);
    char newStr[20] = "";

    int bad_char = 0;
    int add = 0;

    for (s = &maybeMacAddress[0]; *s != '\0'; s++ ) {
        bad_char = 0;
        for (int i = 0; i < 6; i++) {
            if (*s == *badChar[i]) {
                bad_char = 1;
                break;
            }
        }
        if (bad_char == 1) {
            continue;
        }
        else {
            newStr[add] = *s;
            add++;
        }
    }
    int lastIndex = (strlen(newStr) + 1);
    newStr[lastIndex] = '\0';

    // Convert string to lowercase
    toLower(newStr);
    lastIndex = (strlen(newStr) + 1);
    newStr[lastIndex] = '\0';

    int not_alphanumeric_input = 0;

    // We need to check if all char in string are of alphanumeric
    for (s = &newStr[0]; *s != '\0'; s++ ) {
        if (isalpha(*s)) {
        }
        else if (isdigit(*s)) {
        }
        else {
            not_alphanumeric_input = 1;
            break;
        }
    }
    if (not_alphanumeric_input == 1) {
        fprintf(stderr, "Input string %s contains non-alphanumeric characters\n", newStr);
        return "Error";
    }

    if (strlen(newStr) != 12) {
        fprintf(stderr, "Input string %s is not valid len of 12\n", newStr);
        return "Error";
    }

    int delimCounter = 0;
    char delim[1] = "-";
    add = 0;

    for (s = &newStr[0]; *s != '\0'; s++ ) {
        if (delimCounter == 2) {
            lastStr[add] = *delim;
            add++;
            lastStr[add] = *s;
            add++;
            delimCounter = 1;
        }
        else {
            lastStr[add] = *s;
            add++;
            delimCounter++;
        }
    }

    lastIndex = (strlen(lastStr) + 1);
    lastStr[lastIndex] = '\0';

    return lastStr;
}
