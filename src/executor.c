#include <executor.h>


int execute_command(char *command[], char *line, int fifo[]){

    int p = parse_command(command,line), pid, status;

    switch ((pid = fork())){

        case -1:

            perror("fork");
            _exit(1);

        case 0:

            close(fifo[READ]);
            pid = getpid();

            printf("Running PID: %d\n", pid);

            if (write(fifo[WRITE],&pid,sizeof(int)) == -1){

                perror("write");
                _exit(1);
            }

            execvp(command[0],command);
            perror("execvp");
            _exit(1);

        default:

            waitpid(pid,&status,0);

            if (!WIFEXITED(status)){

                perror("son bad termination");
                _exit(1);
            }

            fflush_command(command,p);

            break;
    }

    return 0;
}
