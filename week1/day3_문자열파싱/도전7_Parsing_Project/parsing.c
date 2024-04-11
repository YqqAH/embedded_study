#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#define MAX_HOUR 24

// 구조체 정의: 시간당 로그 개수 저장
typedef struct {
	int hour;
	int count;
} HourlyLogCount;

char dat[250000] = { 0, };
// 비교 함수: HourlyLogCount 구조체를 기반으로 정렬

int main() {
	FILE *fp = fopen("log.txt", "r");

	char buf[1000];
	// 로그 파일 읽기
	while (fgets(buf, 1000, fp)) {
		// Jun 14 15:16:01
		char month[5] = { 0 };
		int day = 0;
		char hour[10] = { 0, };
		sscanf(buf, "%s %d %s", month, &day, hour);


		char logtime[10] = { 0, };
		char* p = strtok(hour, ":");
		strcpy(logtime, p);
		p = strtok(NULL, ":");
		strcat(logtime, p);
		p = strtok(NULL, ":");
		strcat(logtime, p);

		int nlogtime = atoi(logtime);
		dat[nlogtime]++;
		//printf("%s %d\n", logtime, nlogtime);
	}

	fclose(fp);
	int maxvalues[3] = { 0, };
	int maxidx[3] = { 0, };
	//    int first = dat[0];
	//        int second = dat[0];
	//        int third = dat[0];

	for (int i = 1; i < 250000; i++) {
		if (dat[i] > maxvalues[0]) {
			maxvalues[2] = maxvalues[1];
			maxidx[2] = maxidx[1];
			maxvalues[1] = maxvalues[0];
			maxidx[1] = maxidx[0];
			maxvalues[0] = dat[i];
			maxidx[0] = i;
		}
		else if (dat[i] > maxvalues[1] && dat[i] != maxvalues[0]) {
			maxvalues[2] = maxvalues[1];
			maxidx[2] = maxidx[1];
			maxvalues[1] = dat[i];
			maxidx[1] = i;
		}
		else if (dat[i] > maxvalues[2] && dat[i] != maxvalues[1] && dat[i] != maxvalues[0]) {
			maxvalues[2] = dat[i];
			maxidx[2] = i;
		}
	}
	int de = -1;
	for (int i = 0; i < 3; i++) {
		int tophour = maxidx[i];


		// 로그 파일 다시 열기
		fp = fopen("log.txt", "r");

		// 해당 시간대의 로그 출력
		while (fgets(buf, 1000, fp)) {
			char month[5] = { 0 };
			int day = 0;
			char hour[10] = { 0, };
			sscanf(buf, "%s %d %s", month, &day, hour);
			char logtime[10] = { 0, };
			char* p = strtok(hour, ":");
			strcpy(logtime, p);
			p = strtok(NULL, ":");
			strcat(logtime, p);
			p = strtok(NULL, ":");
			strcat(logtime, p);

			int nlogtime = atoi(logtime);
			//printf("%d, %d\n", nlogtime, tophour);
			if (nlogtime == tophour) {
				printf("%s", buf);
			}
		}
		fclose(fp);
	}

	return 0;
}
