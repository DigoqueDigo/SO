#ifndef PACKAGE_H
#define PACKAGE_H

#include <utils.h>

#define INIT_SIZE 2

typedef struct package{
    int protocol;
    int pid;
    char buffer[LINE_SIZE];
    long long int timestamp;
}PACKAGE;


PACKAGE creat_package(int protocol, int pit, char *buffer, long long int timestamp);

void print_package(PACKAGE package);

#endif