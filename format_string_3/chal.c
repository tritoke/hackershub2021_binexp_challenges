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
	char buf[0x100];

	printf("The target is at %p can you change it? ", &target);
	fgets(buf, 0x100, stdin);

	char* lf = strchr(buf, '\n');
	if (lf != NULL) {
		*lf = '\0';
	}

	printf(buf);
	putchar('\n');

	if (target == 42) {
		printf("Wow you are SO cool!!, have a flag: %s\n", FLAG);
	} else {
		printf("no flag for you :P - target = %08x\n", target);
	}

	exit(0);
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
