#include <handle/handle.h>


int handle_tracer(int argc, char** argv, int protocol, int fifo[]){

    ssize_t bytes;
    char buffer[LINE_SIZE] = "";
    int pids_buffer[PIDS_SIZE] = {0};
    char *filename = get_filename("",getpid());

    if (argc > 2 && protocol == STATS_COMMAND_HASH) strcpy(buffer,argv[2]);

    PACKAGE package = creat_package(protocol,getpid(),buffer);

    if (protocol != EXECUTE_HASH){

        int length = 2;

        if (protocol == STATS_COMMAND_HASH) length++;

        length = get_pids_buffer(pids_buffer,argv,length,argc);
        set_package_pids_buffer(&package,pids_buffer,length);
    }

    if (creat_fifo_pid(getpid())) _exit(1);

    printf("%d %d %d %d\n", package.pids_buffer[0],
    package.pids_buffer[1],
    package.pids_buffer[2],
    package.pids_buffer[3]);

    if (write(fifo[WRITE],&package,sizeof(package)) == -1){

        perror("write");
        _exit(1);
    }

    fifo[READ] = open(filename, O_RDONLY, 0666);

    if (fifo[READ] == -1){

        perror("FIFO");
        _exit(1);
    }

    while ((bytes = read(fifo[READ],&package,sizeof(package)))){

        if (bytes != sizeof(package)) _exit(1);

        switch (protocol){

            case STATUS_HASH:

                printf("%d %s %lld ms\n",
                        get_package_pid(package),
                        package.buffer,
                        get_package_timestamp(package));

                break;

            case STATS_TIME_HASH:
                
                printf("Total execution time is %lld ms\n",
                        get_package_timestamp(package));

                break;

            case STATS_COMMAND_HASH:
                
                printf("%s was executed %lld times\n",
                        package.buffer,
                        get_package_timestamp(package));

                break;

            case STATS_UNIQ_HASH:
                perror("not implemented");
                break;
        }

        fflush(stdout);
    }

    close(fifo[READ]);

    if (unlink(filename) == -1) perror("unlink");

    free(filename);

    return 0;
}
