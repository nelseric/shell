#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bits/local_lim.h>

#include "shell.h"

char * hostname;
char * username;
char * prompt;

int main(int argc, char * argv[], char * env[]) {

	char * buf;
	rl_bind_key('\t', rl_abort);

	shell_init();
	prompt = build_prompt();

	while ((buf = readline(prompt)) != NULL) {
		if (strcmp(buf, "exit") == 0) {
			break;
		}
		puts(buf);
	}

	return EXIT_SUCCESS;
}

char * build_prompt() {
	char * cwd = getcwd(NULL, 0);

	char * prompt = calloc(128, sizeof(char));

	sprintf(prompt, "%s@%s:%s$ ", username, hostname, cwd);

	return prompt;
}

void shell_init() {
	username = getenv("USER");

	FILE * hostfile = fopen("/etc/hostname", "r");
	char * hbuff = calloc(HOST_NAME_MAX + 1, sizeof(char));
	char c = fgetc(hostfile);
	int i = 0;
	while (c != EOF) {
		if (c != '\n')
			hbuff[i] = c;
		i++;
		c = fgetc(hostfile);
	}
	hostname = hbuff;
}

