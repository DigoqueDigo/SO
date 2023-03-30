#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define TO_TRACER "totracer"
#define TO_MONITOR "tomonitor"

#define READ 0
#define WRITE 1

#define EXECUTE "execute"
#define STATUS "status"
#define STATS_TIME "stats-time"
#define STATS_COMMAND "stats-command"
#define STATS_UNIQ "stats-uniq"

#define EXECUTE_HASH 0
#define STATUS_HASH 1
#define STATS_TIME_HASH 2
#define STATS_COMMAND_HASH 3
#define STATS_UNIQ_HASH 4

#define LINE_SIZE 2048
#define COMMAND_ARGUMENTS_SIZE 64

int creat_fifos();

int hashcode(char *argument);

#endif