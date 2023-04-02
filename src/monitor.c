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
        _exit(1);
    }

    while ((bytes = read(fifo[READ],&package,sizeof(package)))){

        switch (get_package_protocol(package)){

            case EXECUTE_HASH:

                pid = get_package_pid(package);
                index = get_index_pid(list,pid);

                if (index == -1) add_package(list,package);

                else{

                    remove_package(list,index);

                    switch (fork()){

                        case -1:
                            perror("fork");
                            break;

                        case 0:

                            close(fifo[READ]);
                        
                            save_package(argv[1],package);
                            free_list(list);
                        
                            _exit(0);
                    }
                    // debug
                    sleep(2);
                    show_package(argv[1],pid);
                }

                break;

            case STATUS_HASH:

                if ((pid = fork()) == -1){

                    perror("fork");
                    break;
                }
                
                if (!pid) handle_status(list,package,fifo);

                break;

            case STATS_TIME_HASH:

                if ((pid = fork()) == -1){

                    perror("fork");
                    break;
                }
                
                if (!pid){
                    
                    free_list(list);
                    handle_statstime(package,argv[1],fifo);
                }

                break;


            default:
                perror("Not implemented");
                break;
        }
    }

    free_list(list);
    close(fifo[READ]);

    return 0;
}
