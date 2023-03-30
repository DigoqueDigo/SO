#include <tracer.h>


int main(int argc, char **argv){

    int fifo[2];
  //  ssize_t bytes = 0;
  //  char buffer[LINE_SIZE];
    char *command[COMMAND_ARGUMENTS_SIZE] = {0};

    fifo[WRITE] = open(TO_MONITOR, O_WRONLY, 0666);
    fifo[READ] = open(TO_TRACER, O_RDONLY, 0666);

    if (fifo[WRITE] == -1 || fifo[READ] == -1){

        perror("open fifo");
        return 1;
    }

    if (argc > 1){


        switch (hashcode(argv[1])){

            case -1:
                printf("invalid argument\n");
                fflush(stdout);
                return 1;

            case 0:

                if (argc < 4){

                    printf("missing argument\n");
                    fflush(stdout);
                    return 1;
                }

                switch (argv[2][1]){

                    case 'u':

                        execute_command(command,argv[3],fifo);


                        break;


                    case 'p':

                        break;






                    default:

                        printf("invalid flag\n");
                        fflush(stdout);
                        return 1;
                }

                break;


            case 1:
                perror("not implemented");
                break;

            case 2:
                perror("not implemented");
                break;

            case 3:
                perror("not implemented");
                break;

            case 4:
                perror("not implemented");
                break;
        }
    }




    close(fifo[WRITE]);
    close(fifo[READ]);

    return 0;
}
