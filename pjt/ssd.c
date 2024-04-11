#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (strcmp(argv[1], "W") == 0) {
        FILE* file = NULL;
        if ((file = fopen("nand.txt", "r+")) == NULL) {
            printf("OPEN ERROR\n");
            return 0;
        }
        char address[9];
        long int point = 8 * atoi(argv[2]);
        char* num = argv[2];
        for (int i = 2; i < strlen(argv[3]); i++) {
            address[i - 2] = argv[3][i];
        }
        address[8] = '\0';
        fseek(file, point, SEEK_SET);
        fputs(address, file);
    }
    else if (strcmp(argv[1], "R") == 0) {
        FILE* file = NULL;
        if ((file = fopen("result.txt", "w")) == NULL) {
            printf("OPEN ERROR\n");
            return 0;
        }
        FILE* Rfile = NULL;
        if ((Rfile = fopen("nand.txt", "r")) == NULL) {
            printf("OPEN ERROR\n");
            return 0;
        }
        long int point = 8 * atoi(argv[2]);
        char address[11];
        char temp[10];
        fseek(Rfile, point, SEEK_SET);
        fgets(temp, sizeof(temp), Rfile);
        address[0] = '0';
        address[1] = 'x';
        for (int i = 0; i < 8; i++) {
            address[i + 2] = temp[i];
        }
        address[10] = '\0';
        char* num = argv[2];
        fputs(address, file);
    }

    return 0;
}
