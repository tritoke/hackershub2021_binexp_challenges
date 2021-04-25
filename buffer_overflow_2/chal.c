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

void win(void) {
	printf("Wowie! %s\n", FLAG);
	exit(0);
}

void vuln(void) {
	int canary = 0;
	char buf[100];

	printf("Hi, what's your name? ");
	fgets(buf, 0x100, stdin);

	char* lf = strchr(buf, '\n');
	if (lf != NULL) {
		*lf = '\0';
	}

	if (canary != 0) {
		printf("Hey now I just wanted to be friends >:( canary=%d\n", canary);
		exit(-1);
	}

	printf("\nHi %s, nice to meet you!\n", buf);
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
