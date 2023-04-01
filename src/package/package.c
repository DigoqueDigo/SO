#include <package/package.h>


PACKAGE creat_package(int protocol, int pid, char *buffer){

    PACKAGE new;

    new.protocol = protocol;
    new.pid = pid;
    strcpy(new.buffer,buffer);
    new.timestamp = get_time();

    return new;
}


void set_package_buffer(PACKAGE *package, char *line){

    parse_line_to_package(package->buffer,line);
}


void set_package_timestamp(PACKAGE *package){

    package->timestamp = get_time() - package->timestamp;
}


int get_package_protocol(PACKAGE package){

    return package.protocol;
}


int get_package_pid(PACKAGE package){

    return package.pid;
}


long long int get_package_timestamp(PACKAGE package){

    return package.timestamp;
}


void print_package(PACKAGE package){

    printf("Protocol: %d", package.protocol);
    printf("\t\tPID: %d", package.pid);
    printf("\t\tBuffer: %s", package.buffer);
    printf("\t\tTimestamp: %lld\n", package.timestamp);

    fflush(stdout);
}