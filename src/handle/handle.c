#include <handle/handle.h>


int handle_tracer(int protocol, int fifo[]){

    ssize_t bytes;
    char *filename = get_filename("",getpid());
    PACKAGE package = creat_package(protocol,getpid(),"");

    if (creat_fifo_pid(getpid())) return 1;

    if (write(fifo[WRITE],&package,sizeof(package)) == -1){

        perror("write");
        return 1;
    }

    fifo[READ] = open(filename, O_RDONLY, 0666);

    if (fifo[READ] == -1){

        perror("FIFO");
        return 1;
    }

    while ((bytes = read(fifo[READ],&package,sizeof(package)))){

        if (bytes != sizeof(package)) return 1;

        switch (protocol){

            case STATUS_HASH:

                printf("%d %s %lld ms\n", get_package_pid(package),
                                        package.buffer,
                                        get_package_timestamp(package));

                fflush(stdout);
                break;

            case STATS_TIME_HASH:
                perror("not implemented");
                break;

            case STATS_COMMAND_HASH:
                perror("not implemented");
                break;

            case STATS_UNIQ_HASH:
                perror("not implemented");
                break;
        }
    }

    close(fifo[READ]);

    if (unlink(filename) == -1) perror("unlink");
    
    free(filename);

    return 0;
}