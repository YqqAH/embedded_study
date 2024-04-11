#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write();
void read();
void EXIT();
void help();
void fullwrite();
void fullread();

int main(int argc, char* argv[]) {
	while (1) {
		char input[100];
		printf("Test Shell >> ");
		scanf("%s", input);
		if (strcmp(input, "write") == 0) {
			write();
		}
		else if (strcmp(input, "read") == 0) {
			read();
		}
		else if (strcmp(input, "exit") == 0) {
			EXIT();
			break;
		}
		else if (strcmp(input, "help") == 0) {
			help();
		}
		else if (strcmp(input, "fullwrite") == 0) {
			fullwrite();
		}
		else if (strcmp(input, "fullread") == 0) {
			fullread();
		}
		else if (strcmp(input, "testapp1") == 0) {
			for (int i = 0; i < 100; i++) {
				char command[100];
				sprintf(command, "./ssd W %d 0xABCDABCD", i);
				system(command);
			}
			for (int i = 0; i < 100; i++) {
				char command[100];
				sprintf(command, "./ssd R %d", i);
				system(command);
				FILE* fs;
				fs = fopen("result.txt", "r");
				char str[100];
				fgets(str, 100, fs);
				printf("%s\n", str);
				fclose(fs);
			}
		}
		else if (strcmp(input, "testapp2") == 0) {
			for (int y = 0; y < 30; y++) {
				for (int x = 0; x < 5; x++) {
					char command[100];
					sprintf(command, "./ssd W %d 0xAAAABBBB", x);
					system(command);
				}
			}
			for (int x = 0; x < 5; x++) {
				char command[100];
				sprintf(command, "./ssd W %d 0x12345678", x);
				system(command);
			}
			for (int x = 0; x < 5; x++) {
				char command[100];
				sprintf(command, "./ssd R %d", x);
				system(command);
				FILE* fs;
				fs = fopen("result.txt", "r");
				char str[100];
				fgets(str, 100, fs);
				printf("%s\n", str);
				fclose(fs);
			}
		}
		else {
			printf("INVALID COMMAND\n");
		}
	}
	return 0;
}

void write() {
	int LBA;
	char data[20];
	scanf("%d", &LBA);
	if (LBA < 0 || LBA >= 100) {
		printf("INVALID COMMAND\n");
		return;
	}
	scanf("%s", data);
	int flag = 1;
	for(int i=2; i<10; i++){
		if(('A' <= data[i] && data[i] <= 'F') || ('0' <= data[i] && data[i] <= '9')){
			flag = 1;
		}
		else{
			flag = 0;
			break;
		}
	}
	if(flag ==0){
		printf("INVALID COMMAND\n");
		return;
	}
	char command[100];
	sprintf(command, "./ssd W %d %s", LBA, data);
	system(command);
}

void read() {
	int LBA;
	scanf("%d", &LBA);
	if (LBA < 0 || LBA >= 100) {
		printf("INVALID COMMAND\n");
		return;
	}
	char command[100];
	sprintf(command, "./ssd R %d", LBA);
	system(command);
	FILE* fs;
	fs = fopen("result.txt", "r");
	char str[100];
	fgets(str, 100, fs);
	printf("%s\n", str);
	fclose(fs);
}

void EXIT() {
	printf("exit 입력되었습니다.\n\n");
	printf("Test Shell을 종료합니다.\n");
}

void help() {
	printf("help 입력되었습니다.\n\n");
	printf("help 출력...\n");
}

void fullwrite() {
	char data[20];
	scanf("%s", data);
	
	int flag = 1;
	for(int i=2; i<10; i++){
		if(('A' <= data[i] && data[i] <= 'F') || ('0' <= data[i] && data[i] <= '9')){
			flag = 1;
		}
		else{
			flag = 0;
			break;
		}
	}
	if(flag ==0){
		printf("INVALID COMMAND\n");
		return;
	}

	for (int i = 0; i < 100; i++) {
		char command[100];
		sprintf(command, "./ssd W %d %s", i, data);
		system(command);
	}
}

void fullread() {
	for (int i = 0; i < 100; i++) {
		char command[100];
		sprintf(command, "./ssd R %d", i);
		system(command);
		FILE* fs;
		fs = fopen("result.txt", "r");
		char str[100];
		fgets(str, 100, fs);
		printf("%s\n", str);
		fclose(fs);
	}
}
