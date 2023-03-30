#include <monitor.h>


int main(void){

    int fifo[2];
 //   char buffer[LINE_SIZE] = {0};
    ssize_t bytes = 0;

    if (creat_fifos()) return 1;

    fifo[READ] = open(TO_MONITOR, O_RDONLY, 0666);
    fifo[WRITE] = open(TO_TRACER, O_WRONLY, 0666);

    if (fifo[WRITE] == -1 || fifo[READ] == -1){

        perror("open fifo");
        return 1;
    }

    int pid;

    while ((bytes = read(fifo[READ],&pid,sizeof(int)))){

    /*    if (write(STDOUT_FILENO,&pid,bytes) == -1){

            perror("write");
            return 1;
        }*/

        printf("pid: %d\n", pid);
    }


    close(fifo[READ]);
    close(fifo[WRITE]);

    return 0;
}