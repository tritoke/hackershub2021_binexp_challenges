#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vuln(void);
void setup(void);

const char binsh[] = "/bin/sh";
void gadget(void) {
	__asm__ ("pop %rdi;\
	          ret");
}

int main(void) {
	// setup for the challenge
	setup();

	vuln();

	return 0;
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
	printf("You seem pretty cool, have a sneak peak of whats on the server :)\n");
	system("ls");
}

void setup(void) {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}
