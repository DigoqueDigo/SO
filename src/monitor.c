#include <monitor.h>


int main(int argc, char **argv){

    if (argc != 2){

        printf(RED "Invalid arguments\n" RESET);
        fflush(stdout);
        _exit(1);
    }

    PACKAGE package;
    ssize_t bytes = 0;
    int fifo[2], pid, index;

    LIST list = init_list();

    if (creat_fifos()) _exit(1);

    fifo[READ] = open(TO_MONITOR, O_RDONLY, 0666);
    fifo[WRITE] = open(TO_TRACER, O_WRONLY, 0666);

    if (fifo[WRITE] == -1 || fifo[READ] == -1){

        perror("open fifo");
        return 1;
    }

    while ((bytes = read(fifo[READ],&package,sizeof(package)))){

        switch (get_package_protocol(package)){

            case EXECUTE_HASH:

                pid = get_package_pid(package);
                index = get_index_pid(list,pid);

                if (index == -1) add_package(list,package);

                else{

                    remove_package(list,pid);
                    save_package(argv[1],package);
                    show_package(argv[1],pid);
                }

                break;

            default:

                printf(RED "Unknow protocol" RESET);
                fflush(stdout);
                break;
        }
    }

    free_list(list);

    close(fifo[READ]);
    close(fifo[WRITE]);

    return 0;
}