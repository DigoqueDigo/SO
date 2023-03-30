#include <pipeline.h>


int execute_pipeline(char *command[], char *line, int fifo[]){

    struct timeval clock;
    long long int time_elapsed;
    int pipeline[PIPES][2], pipe_index = 0, index = 0, start = 0, length, pid, status;

    length = parse_command(command,line);

    gettimeofday(&clock,NULL);
    time_elapsed = convert_time(&clock);

    printf(MAG "Running PID %d\n" RESET, getpid());
    fflush(stdout);

    for (char *token = command[index]; token != NULL; token = command[++index]){

        if (!strcmp(token,"|")){

            if (pipe(pipeline[pipe_index]) == -1){

                perror("pipe");
                _exit(1);
            }

            switch (fork()){

                case -1:
                    perror("fork");
                    _exit(1);

                case 0:

                    close(fifo[READ]);
                    close(fifo[WRITE]);
                    close(pipeline[pipe_index][READ]);

                    if (pipe_index){

                        dup2(pipeline[pipe_index-1][READ],STDIN_FILENO);
                        close(pipeline[pipe_index-1][READ]);
                    }

                    dup2(pipeline[pipe_index][WRITE],STDOUT_FILENO);
                    close(pipeline[pipe_index][WRITE]);
                    
                    command[index] = NULL;

                    execvp(command[start],command+start);
                    perror("execss");
                    _exit(1);

                default:

                    close(pipeline[pipe_index][WRITE]);

                    if (pipe_index) close(pipeline[pipe_index-1][READ]);
                    
                    pipe_index++;
                    start = index+1;
            }
        }
    }

    if (pipe_index){
        
        dup2(pipeline[pipe_index-1][READ],STDIN_FILENO);
        close(pipeline[pipe_index-1][READ]);
    }

    switch ((pid = fork())){

        case -1:
            perror("fork");
            _exit(1);

        case 0:
            execvp(command[start],command+start);
            perror("exec");
            _exit(1);
    }

    waitpid(pid,&status,0);

    gettimeofday(&clock,NULL);
    time_elapsed = convert_time(&clock) - time_elapsed;

    if (!WIFEXITED(status)){

        perror("son bad termination");
        _exit(1);
    }

    printf(MAG "Ended in %lld ms\n" RESET, time_elapsed);
    
    fflush(stdout);
    fflush_command(command,length);

    return 0;
}