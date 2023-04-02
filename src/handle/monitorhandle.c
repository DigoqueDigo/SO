#include <handle/monitorhandle.h>


void handle_monitor(PACKAGE package, char *path, int fifo[]){

    PACKAGE result;
    long long int acc = 0, total = 0;
    int pipes[PIPES][2], index = 0, fd;
    char buffer[LINE_SIZE] = {0}, *filename;

    filename = get_filename("",get_package_pid(package));

    fifo[WRITE] = open(filename, O_WRONLY, 0666);

    if (fifo[WRITE] == -1){

        free(filename);
        perror("open FIFO");
        _exit(1);
    }

    free(filename);

    for (int p = 0; p < get_package_pids_buffer_size(package); p += BUCKET, index++){

        if (pipe(pipes[index]) == -1){

            perror("pipe");
            _exit(1);
        }

        switch (fork()){

            case -1:
                perror("fork");
                _exit(1);

            case 0:

                close(pipes[index][READ]);

                for (int i = p; i < p+BUCKET && get_package_pids_buffer_pid(package,i) != -1; i++){

                    filename = get_filename(path,get_package_pids_buffer_pid(package,i));

                    fd = open(filename, O_RDONLY, 0666);

                    if (fd == -1){

                        free(filename);
                        perror("open");
                        _exit(1);
                    }

                    if (read(fd,&result,sizeof(PACKAGE)) != sizeof(PACKAGE)){

                        free(filename);
                        perror("read");
                        _exit(1);
                    }

                    switch (get_package_protocol(package)){

                        case STATS_TIME_HASH:
                            acc += get_package_timestamp(result);
                            break;

                        case STATS_COMMAND_HASH:
                            acc += count_occurrence(result.buffer,package.buffer);
                            break;

                        case STATS_UNIQ_HASH:

                            buffer[0] = '\0';

                            if (!strstr(result.buffer,"|")) strcpy(buffer,result.buffer);

                            break;
                    }

                    free(filename);
                    close(fd);
                }

                result = creat_package(get_package_protocol(package),0,buffer);
                set_package_timestamp_force(&result,acc);

                if (write(pipes[index][WRITE],&result,sizeof(PACKAGE)) == -1){

                    free(filename);
                    perror("write");
                    _exit(1);
                }

                close(pipes[index][WRITE]);
                _exit(0);

            default:

                close(pipes[index][WRITE]);
                break;
        }
    }

    for (int p = 0; p < index; p++){

        if (read(pipes[p][READ],&result,sizeof(PACKAGE)) != sizeof(PACKAGE)){

            perror("read");
            _exit(1);
        }
        
        total += get_package_timestamp(result);
        
        if (result.buffer[0]){
            
            strcat(buffer,result.buffer);
            strcat(buffer,"\n");
        }

        close(pipes[p][READ]);
    }

    if (get_package_protocol(package) == STATS_COMMAND_HASH) strcpy(buffer,package.buffer);

    result = creat_package(get_package_protocol(package),0,buffer);
    set_package_timestamp_force(&result,total);

    if (write(fifo[WRITE],&result,sizeof(PACKAGE)) == -1){

        perror("write");
        _exit(1);
    }

    close(fifo[WRITE]);
    _exit(0);
}
