#include <parser.h>


int parse_command(char *command[], char *line){

    int p = 0;

    for (char *token = strsep(&line," "); token; token = strsep(&line," ")){

        if (token[0] == '\"'){

            char buffer[LINE_SIZE] = {0};

            strcat(buffer,token+1);

            if (token[strlen(token)-1] != '\"'){

                token = strsep(&line,"\"");

                strcat(buffer," ");
                strcat(buffer,token);

                token = strsep(&line," ");
            }

            else buffer[strlen(buffer)-1] = '\0';

            command[p++] = strdup(buffer);

        }

        else command[p++] = strdup(token);
    }

    return p;
}


void parse_line_to_package(char *buffer, char *line){

    int ant = 1;

    for (char *token = strsep(&line," "); token; token = strsep(&line," ")){

        if (ant){

            strcat(buffer,token);
            ant = 0;
        }

        if (!strcmp(token,"|")){

            ant = 1;
            strcat(buffer," | ");
        }
    }
}


void fflush_command(char *command[], int length){

    for (int p = 0; p < length; p++){

        free(command[p]);
        command[p] = NULL;
    }
}


void nub(char *src, char *delim){

    int p, index = 0;
    char *src_clone = strdup(src), *temp = src_clone;
    char *buffer[COMMAND_ARGUMENTS_SIZE] = {NULL};

    for (char *token = strsep(&src_clone,delim); token; token = strsep(&src_clone,delim)){
    
        for (p = 0; p < index; p++){

            if (!strcmp(token,buffer[p])) break;
        }

        if (p == index && *token) buffer[index++] = strdup(token);
    }

    memset(src,0,LINE_SIZE*sizeof(char));

    for (p = 0; p < index; p++){

        strcat(src,buffer[p]);
        strcat(src,delim);
    }

    free(temp);
    fflush_command(buffer,index);
}