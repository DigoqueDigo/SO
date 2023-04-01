#include <pipeline.h>


int execute_pipeline(char *command[], char *line, int fifo[]){

    PACKAGE package;
    char line_clone[LINE_SIZE];
    int pipeline[PIPES][2], pipe_index = 0, index = 0, start = 0, length, pid, status;

    memmove(line_clone,line,strlen(line)*sizeof(char));
    length = parse_command(command,line);

    printf(MAG "Running PID %d\n" RESET, getpid());
    fflush(stdout);

    package = creat_package(EXECUTE_HASH,getpid(),"");
    set_package_buffer(&package,line_clone);

    print_package(package);

    if (write(fifo[WRITE],&package,sizeof(package)) == -1){

        perror("write");
        _exit(1);
    }

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

    if (!WIFEXITED(status)){

        perror("son bad termination");
        _exit(1);
    }

    set_package_timestamp(&package);
    print_package(package);

    printf(MAG "Ended in %lld ms\n" RESET, get_package_timestamp(&package));

    if (write(fifo[WRITE],&package,sizeof(package)) == -1){

        perror("write");
        _exit(1);
    }
    
    fflush(stdout);
    fflush_command(command,length);

    return 0;
}