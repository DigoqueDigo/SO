#include <package/package.h>


PACKAGE creat_package(int protocol, int pid, char *buffer, long long int timestamp){

    PACKAGE new;

    new.protocol = protocol;
    new.pid = pid;
    strcpy(new.buffer,buffer);
    new.timestamp = timestamp;

    return new;
}


void print_package(PACKAGE package){

    printf("Protocol: %d", package.protocol);
    printf("\tPID: %d", package.pid);
    printf("\tBuffer: %s", package.buffer);
    printf("\tTimestamp: %lld\n", package.timestamp);

    fflush(stdout);
}
