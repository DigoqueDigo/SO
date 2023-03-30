#include <parser.h>


int parse_command(char *command[], char *line){

    int p = 0;

    for (char *token = strsep(&line, " "); token; token = strsep(&line," ")){

        command[p++] = strdup(token);
    }

    return p;
}


void fflush_command(char *command[], int length){

    for (int p = 0; p < length; p++){

        free(command[p]);
        command[p] = NULL;
    }
}
