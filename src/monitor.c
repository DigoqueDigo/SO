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

    if (creat_fifo()) _exit(1);

    fifo[READ] = open(TO_MONITOR, O_RDONLY, 0666);

    if (fifo[READ] == -1){

        perror("open fifo");
        return 1;
    }

    while ((bytes = read(fifo[READ],&package,sizeof(package)))){

        switch (get_package_protocol(package)){

            case -1:

                perror("protocol");
                break;

            case EXECUTE_HASH:

                pid = get_package_pid(package);
                index = get_index_pid(list,pid);

                if (index == -1) add_package(list,package);

                else{

                    remove_package(list,index);
                    save_package(argv[1],package);
                    // debug
                    sleep(2);
                    show_package(argv[1],pid);
                }

                break;

            case STATUS_HASH:

                switch (fork()){

                    case -1:
                        perror("fork");
                        break;

                    case 0:{

                        close(fifo[READ]);
                        char *filename = get_filename("",get_package_pid(package));

                        fifo[WRITE] = open(filename, O_WRONLY, 0666);

                        if (fifo[WRITE] == -1){

                            perror("open FIFO");
                            break;
                        }

                        for (int p = 0; p < get_list_size(list); p++){

                            package = get_pakage(list,p);
                            set_package_timestamp(&package);

                            if (write(fifo[WRITE],&package,sizeof(package)) == -1){

                                perror("write");
                                _exit(1);
                            }
                        }

                        free(filename);

                        close(fifo[WRITE]);
                        _exit(0);
                    }
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

    return 0;
}
