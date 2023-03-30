#ifndef PARSER_H
#define PARSER_H

#include <utils.h>

int parse_command(char *command[], char *line);

void fflush_command(char *command[], int length);

#endif