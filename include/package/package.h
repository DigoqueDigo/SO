#ifndef PACKAGE_H
#define PACKAGE_H

#include <utils.h>
#include <parser.h>

#define INIT_SIZE 2

typedef struct package{
    int protocol;
    int pid;
    char buffer[LINE_SIZE];
    int pids_buffer[PIDS_SIZE];
    long long int timestamp;
}PACKAGE;


PACKAGE creat_package(int protocol, int pit, char *buffer);

void set_package_buffer(PACKAGE *package, char *line);

void set_package_pids_buffer(PACKAGE *package, int *pids, int size);

void set_package_timestamp(PACKAGE *package);

void set_package_timestamp_force(PACKAGE *package, long long int value);

int get_package_protocol(PACKAGE package);

int get_package_pid(PACKAGE package);

int get_package_pids_buffer_size(PACKAGE package);

int get_package_pids_buffer_pid(PACKAGE package, int index);

long long int get_package_timestamp(PACKAGE package);

void print_package(PACKAGE package);

#endif