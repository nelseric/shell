#ifndef SHELL_H
#define SHELL_H


char * build_prompt();
void shell_init();
void shell(const char *);

#define CMD_INIT 0
#define CMD_TOKEN 1
#define CMD_SUB 2



#define _XOPEN_SOURCE

#endif
