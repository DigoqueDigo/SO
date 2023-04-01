#ifndef PACKAGE_H
#define PACKAGE_H

#include <utils.h>
#include <parser.h>

#define INIT_SIZE 2

typedef struct package{
    int protocol;
    int pid;
    char buffer[LINE_SIZE];
    long long int timestamp;
}PACKAGE;


PACKAGE creat_package(int protocol, int pit, char *buffer);

void set_package_buffer(PACKAGE *package, char *line);

void set_package_timestamp(PACKAGE *package);

int get_package_protocol(PACKAGE package);

int get_package_pid(PACKAGE package);

long long int get_package_timestamp(PACKAGE *package);

void print_package(PACKAGE package);

#endif