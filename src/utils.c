#include <utils.h>

int creat_fifos(){

    if (mkfifo(TO_MONITOR,0666) || mkfifo(TO_TRACER,0666)){

        if (errno != EEXIST){

            perror("make fifos");
            return 1;
        }
    }

    return 0;
}


int hashcode(char *argument){

    int hash = -1;
    char *options[] = {EXECUTE, STATUS, STATS_TIME, STATS_COMMAND, STATS_UNIQ};

    for (int p = 0; hash == -1 && p < 5; p++){

        if (!strcmp(argument,options[p])) hash = p;
    }

    return hash;
}


long long int convert_time(struct timeval *clock){

    return clock->tv_sec*1000 + clock->tv_usec/1000; 
}