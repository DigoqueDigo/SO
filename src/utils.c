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

    filename[0] = '\0';
    strcat(filename,path);
    strcat(filename,buffer);

    return filename;
}


int get_pids_buffer(int *pids, char **argv, int start, int end){

    for (int p = 0; p < end-start; p++){

        pids[p] = atoi(argv[start+p]);
    }

    return end - start;
}


int count_occurrence(char *buffer, char *key){

    int acc = 0;

    for (char *token = strstr(buffer,key); token; acc++){

        token = strstr(token+1,key);
    }

    return acc;
}
