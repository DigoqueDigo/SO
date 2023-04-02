#include <handle/statstime.h>


void handle_statstime(PACKAGE package, char *path, int fifo[]){

    PACKAGE result;
    int pipes[PIPES][2], index = 0, fd;
    long long int acc = 0, total_time = 0;
    char *filename = get_filename("",get_package_pid(package));

    fifo[WRITE] = open(filename, O_WRONLY, 0666);

    if (fifo[WRITE] == -1){

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

                    if (read(fd,&result,sizeof(package)) != sizeof(package)){

                        free(filename);
                        perror("read");
                        _exit(1);
                    }

                    acc += get_package_timestamp(result);
                    
                    free(filename);
                    close(fd);
                }

                if (write(pipes[index][WRITE],&acc,sizeof(long long int)) == -1){

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

        if (read(pipes[p][READ],&acc,sizeof(long long int)) != sizeof(long long int)){

            perror("read");
            _exit(1);
        }

        total_time += acc;

        close(pipes[p][READ]);
    }

    result = creat_package(STATS_TIME_HASH,0,"");
    set_package_timestamp_force(&result,total_time);

    if (write(fifo[WRITE],&result,sizeof(package)) == -1){

        perror("write");
        _exit(1);
    }

    close(fifo[WRITE]);
    _exit(0);
}