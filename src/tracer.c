#include <tracer.h>


int main(int argc, char **argv){

    int fifo[2];
    
    fifo[WRITE] = open(TO_MONITOR, O_WRONLY, 0666);

    if (fifo[WRITE] == -1){

        perror("open fifo");
        _exit(1);
    }

    if (argc > 1){

        switch (hashcode(argv[1])){

            case -1:

                printf(RED "Invalid argument\n" RESET);
                fflush(stdout);
                _exit(1);


            case EXECUTE_HASH:

                if (argc < 4){

                    printf(RED "Missing argument\n" RESET);
                    fflush(stdout);
                    _exit(1);
                }

                if (argv[2][1] == 'u' || argv[2][1] == 'p'){

                    execute_pipeline(argv[3],fifo);
                }

                else{

                    printf(RED "Invalid flag\n" RESET);
                    fflush(stdout);
                }

                break;


            default:

                handle_tracer(hashcode(argv[1]),fifo);
                break;
        }
    }

    close(fifo[WRITE]);

    return 0;
}
