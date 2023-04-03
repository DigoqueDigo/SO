#ifndef PARSER_H
#define PARSER_H

#include <utils.h>

int parse_command(char *command[], char *line);

void parse_line_to_package(char *buffer, char *line);

void fflush_command(char *command[], int length);

void nub(char *src, char *delim);

#endif