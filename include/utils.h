#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

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

#define BUCKET 1
#define PIPES 256
#define LINE_SIZE 2048
#define PIDS_SIZE 512
#define FILENAME_SIZE 128
#define COMMAND_ARGUMENTS_SIZE 512

#define MAG   "\x1B[35m"
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int creat_fifo();

int creat_fifo_pid(int pid);

int hashcode(char *argument);

long long int get_time();

char* get_filename(char *path, int pid);

int get_pids_buffer(int *pids, char **argv, int start, int end);

#endif