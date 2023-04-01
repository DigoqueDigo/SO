#include <utils.h>


int creat_fifo(){

    if (mkfifo(TO_MONITOR,0666) && errno != EEXIST){

        perror("creat FIFO tomonitor");
        return 1;
    }

    return 0;
}


int creat_fifo_pid(int pid){

    char buffer[FILENAME_SIZE];

    snprintf(buffer,FILENAME_SIZE,"%d",pid);

    if (mkfifo(buffer,0666)){

        perror("creat FIFO do tracer");
        return 1;
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


long long int get_time(){

    struct timeval clock;
    gettimeofday(&clock,NULL);

    return clock.tv_sec*1000 + clock.tv_usec/1000; 
}


char* get_filename(char *path, int pid){

    char buffer[FILENAME_SIZE];
    char *filename = malloc(FILENAME_SIZE);

    snprintf(buffer,FILENAME_SIZE,"%d",pid);

    strcat(filename,path);
    strcat(filename,buffer);

    return filename;
}