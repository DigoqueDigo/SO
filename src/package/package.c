#include <package/package.h>


PACKAGE creat_package(int protocol, int pid, char *buffer){

    PACKAGE new;

    new.protocol = protocol;
    new.pid = pid;
    memset(new.buffer,0,LINE_SIZE*sizeof(char));
    memset(new.pids_buffer,-1,PIDS_SIZE*sizeof(int));
    strcpy(new.buffer,buffer);
    new.timestamp = get_time();

    return new;
}


void set_package_buffer(PACKAGE *package, char *line){

    parse_line_to_package(package->buffer,line);
}


void set_package_pids_buffer(PACKAGE *package, int *pids, int size){

    memmove(package->pids_buffer,pids,size*sizeof(int));
}


void set_package_timestamp(PACKAGE *package){

    package->timestamp = get_time() - package->timestamp;
}


void set_package_timestamp_force(PACKAGE *package, long long int value){

    package->timestamp = value;
}


int get_package_protocol(PACKAGE package){

    return package.protocol;
}


int get_package_pid(PACKAGE package){

    return package.pid;
}


int get_package_pids_buffer_size(PACKAGE package){

    int p = 0;

    for (; p < PIDS_SIZE && package.pids_buffer[p] != -1; p++);

    return p;
}


int get_package_pids_buffer_pid(PACKAGE package, int index){

    if (index < PIDS_SIZE) return package.pids_buffer[index];

    return -1;
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