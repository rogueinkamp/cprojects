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
    /* printf("\nResults of New String: %s \n", newStr); */

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

const char* convert_mac_addr_str_std_fmt_noprint(char *maybeMacAddress) {
    printf("maybeMacAddress: %s\n", maybeMacAddress);
    char* s;
    char *badChar[6] = {"[", ".", ":", "-", "]", " "};

    int strLen = strlen(maybeMacAddress);
    char newStr[20];
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

    toLower(newStr);
    lastIndex = (strlen(newStr) + 1);
    newStr[lastIndex] = '\0';

    int alphanumeric = 0;

    // We need to check if all char in string are of alphanumeric
    for (int i = 0; newStr[i] != '\0'; ++i) {
    /* for (s = &newStr[0]; *s != '\0'; s++ ) { */
        if (isalpha(newStr[i])) {
            printf("isalpha=True: %c\n", newStr[i]);
            alphanumeric = 1;
        }
        else if (isdigit(newStr[i])) {
            printf("isdigit=True: %c\n", newStr[i]);
            alphanumeric = 1;
        }
    }

    if (alphanumeric == 0) {
        printf("NewStr: %s\n", newStr);
        fprintf(stderr, "Input string %s contains non-alphanumeric characters\n", newStr);
        return "Error";
    }

    if (strlen(newStr) != 14) {
        printf("NewStr: %s\n", newStr);
        printf("NewStrLen: %i\n", (int) strlen(newStr));
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
const char* convert_mac_addr_str_std_fmt_print(char *maybeMacAddress) {
    /* char str[100]; */
    /* printf("Enter the string > "); */
    /* scanf("%[^\n]", str); */
    /* scanf("%10[0-9a-zA-Z ]", str); */
    /* scanf("%s", str); */
    /* printf("Entered Sentence is: %s\n\n", str); */

    char str[18] = "00.80.41.ae.fd.7e";

    /* char* token; */
    /* char* rest = str; */
    /* char *array[10]; */
    /* int i = 0; */

    /* while ((token = strtok_r(rest, ":", &rest))) { */
    /*     printf("split = %s\n", token); */
    /*     array[i++] = token; */
    /* } */

    /* for (i = 0; i < (int) sizeof(array)/sizeof(array[0]); ++i)  */
    /*     printf("ELEMENT OF ARRAY -> %s\n", array[i]); */

    /* i = 0; */
    /* int j = 0; */
    /* char a; */

    char* s;
    char *badChar[6] = {"[", ".", ":", "-", "]", " "};
    /* char * replace = ""; */
    /* char *str_char; */

    int strLen = strlen(str);
    char newStr[20] = "";

    /* printf("str 2 index = %c\n", str[2]); */
    /* printf("\nstrlen str: %i \n", strLen); */

    int bad_char = 0;
    int add = 0;
    for (s = &str[0]; *s != '\0'; s++ ) {
        /* printf("char to check [ %c ]\n", *s); */
        bad_char = 0;
        for (int i = 0; i < 6; i++) {
            if (*s == *badChar[i]) {
                /* printf("\n%c is bad match of %c\n", *s, *badChar[i]); */
                bad_char = 1;
                break;
            }
        }
        if (bad_char == 1) {
            /* printf("bad char %c - continue to next char in string\n", *s); */
            continue;
        }
        else {
            /* printf("new_str_index: %i add: %c to new string\n", add, *s); */
            newStr[add] = *s;
            add++;
        }
    }

    int lastIndex = (strlen(newStr) + 1);
    newStr[lastIndex] = '\0';
    printf("\nResults of New String: %s \n", newStr);

    /* remove_spaces(newStr); */

    /* lastIndex = (strlen(newStr) + 1); */
    /* newStr[lastIndex] = '\0'; */
    /* printf("\nResults of New String After Spaces removed: %s \n", newStr); */

    toLower(newStr);
    lastIndex = (strlen(newStr) + 1);
    newStr[lastIndex] = '\0';
    printf("\nResults of New String After LowerCase: %s \n", newStr);

    int not_alphanumeric_input = 0;

    // We need to check if all char in string are of alphanumeric
    for (s = &newStr[0]; *s != '\0'; s++ ) {
        if (isalpha(*s)) {
            /* printf("This is ok: %c\n", *s); */
        }
        else if (isdigit(*s)) {
            /* printf("This is ok too: %c\n", *s); */
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
        fprintf(stderr, "Input string %c is not valid len of 12\n", *newStr);
        return "Error";
    }

    printf("Congradulations, this looks like a valid mac address! %s\n", newStr);

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
    printf("Congradulations! ORIGINAL: %s -> CONVERTED: %s\n", newStr, lastStr);

    return lastStr;
}

int main() {
    const char * ret;
    char str[18] = "00.80.41.ae.fd.7e";
    ret = convert_mac_addr_str_std_fmt_noprint(str);
    printf("Congradulations! ORIGINAL: %s -> CONVERTED: %s\n", str, ret);
    return 0;
}

