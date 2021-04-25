#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flag.h"

void vuln(void);
void setup(void);

int main(void) {
	// setup for the challenge
	setup();

	vuln();

	return 0;
}

void vuln(void) {
	int target = 0;
	char buf[100];

	printf("Hi, what's your name? ");
	fgets(buf, 0x100, stdin);

	char* lf = strchr(buf, '\n');
	if (lf != NULL) {
		*lf = '\0';
	}

	printf("\nHi %s, nice to meet you!\n", buf);

	if (target == 42) {
		printf("Nice job, here's your flag: %s\n", FLAG);
	} else {
		printf("Nah thats not it chief, target = %d\n", target);
	}

	exit(0);
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
