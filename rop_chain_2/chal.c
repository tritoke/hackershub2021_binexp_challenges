#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flag.h"

int shift = -1;
int gamer = 0;
int byte = 0;

void vuln(void);
void setup(void);

int main(void) {
	// setup for the challenge
	setup();

	vuln();

	return 0;
}

void set_shift_0(void) {
	shift = 0;
}

void set_shift_8(void) {
	shift = 8;
}

void set_shift_16(void) {
	shift = 16;
}

void set_shift_24(void) {
	shift = 24;
}

void set_byte_DE(void) {
	byte = 0xDE;
}

void set_byte_AD(void) {
	byte = 0xAD;
}

void set_byte_BE(void) {
	byte = 0xBE;
}

void set_byte_EF(void) {
	byte = 0xEF;
}

void become_gamer(void) {
	gamer |= byte << shift;
}

void win(void) {
	if (gamer == 0xDEADBEEF) {
		printf("Epic gamer moment!!!! %s\n", FLAG);
	} else {
		printf("Sad gamer moment :'(\n.");
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
