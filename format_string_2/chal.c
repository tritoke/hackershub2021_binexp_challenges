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
	char buf[0x100];
	char flag[] = FLAG;

	printf("The flag is here: %p - can you find it ;)\n", flag);
	fgets(buf, 0x100, stdin);

	char* lf = strchr(buf, '\n');
	if (lf != NULL) {
		*lf = '\0';
	}

	printf(buf);
	putchar('\n');

	exit(0);
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
