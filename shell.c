#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bits/local_lim.h>
#include <wordexp.h>
#include <errno.h>

char * hostname;
char * username;
char * home_dir;
char * prompt;

int main(int argc, char * argv[], char * env[]) {

    char * buf;
    shell_init();
    prompt = build_prompt();

    while ((buf = readline(prompt)) != NULL) {
        if (buf[0] != 0) {
            shell(buf);
            add_history(buf);
        }
        prompt = build_prompt();
    }

    return EXIT_SUCCESS;
}

void shell(const char * cmd) {
    wordexp_t * wx = malloc(sizeof(wordexp_t));
    //*
    int err = 0;
    if ((err = wordexp(cmd, wx, WRDE_SHOWERR)) == 0) {

        if (strcmp(wx->we_wordv[0], "quit") == 0
                || strcmp(wx->we_wordv[0], "exit") == 0) {
            exit(0);
        } else if (strcmp(wx->we_wordv[0], "cd") == 0) {
            if (wx->we_wordc > 1) {
                if (chdir(wx->we_wordv[1]) != 0)
                    fprintf(stderr, "%s\n", strerror(errno));
            } else {
                if (chdir("/") != 0)
                    fprintf(stderr, "%s\n", strerror(errno));
            }
        } else {
            if (!fork()) {
                if (execvp(wx->we_wordv[0], wx->we_wordv) == -1) {
                    perror("execvp");
                    exit(1);
                }
            } else {
                wait(NULL);
            }
        }

    }

    //*/
    wordfree(wx);
}

char * build_prompt() {
    char * cwd = getcwd(NULL, 0);
    char * c = strstr(cwd, home_dir);
    if (c != NULL) {
        char * tmp = calloc(strlen((char*) (cwd + strlen(home_dir)) + 2),
                sizeof(char));
        tmp[0] = '~';
        strcat(tmp, (char*) (cwd + strlen(home_dir)));
        cwd = tmp;
    }

    char * prompt = calloc(128, sizeof(char));

    sprintf(prompt, "\e[1;34m%s\e[0m@\e[1;32m%s\e[0;m:\e[0;31m%s\e[0m$ ",
            username, hostname, cwd);

    return prompt;
}

void shell_init() {
    username = getenv("USER");
    home_dir = getenv("HOME");

    hostname = getenv("HOSTNAME");
    if( strlen(hostname) == 0){
        FILE * hostfile = fopen("/etc/hostname", "r");
        if(hostfile != NULL){
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
    }
}

