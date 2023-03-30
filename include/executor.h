#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <utils.h>
#include <parser.h>

int execute_command(char *command[], char *line, int fifo[]);

#endif