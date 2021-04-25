#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flag.h"

int poggers = 0;

void vuln(void);
void setup(void);

int main(void) {
	// setup for the challenge
	setup();

	vuln();

	return 0;
}

void gadget(void) {
	poggers = 42;
}

void win(void) {
	if (poggers == 42) {
		printf("Lets go gamers! %s\n", FLAG);
	} else {
		printf("Wow that is NOT pog :cry:\n.");
	}
	exit(0);
}

void vuln(void) {
	char buf[100];

	printf("Hi, what's your name? ");
	fgets(buf, 0x100, stdin);

	char* lf = strchr(buf, '\n');
	if (lf != NULL) {
		*lf = '\0';
	}

	printf("Hi %s, nice to meet you!\n", buf);
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
