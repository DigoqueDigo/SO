#include <executor.h>


int execute_command(char *command[], char *line, int fifo[]){

    struct timeval clock;

    int p = parse_command(command,line), pid, status;

    long long int *time_elapsed = (long long int*) mmap(NULL, sizeof (int), 
                            PROT_READ | PROT_WRITE,
                    	    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    switch ((pid = fork())){

        case -1:
            perror("fork");
            _exit(1);

        case 0:

            close(fifo[READ]);
            pid = getppid();

            printf(MAG "Running PID: %d\n" RESET, pid);
            fflush(stdout);

            gettimeofday(&clock,NULL);
            *time_elapsed = convert_time(&clock);

            if (write(fifo[WRITE],&pid,sizeof(int)) == -1){

                perror("write");
                _exit(1);
            }

            execvp(command[0],command);
            perror("execvp");
            _exit(1);

        default:

            waitpid(pid,&status,0);

            gettimeofday(&clock,NULL);
            *time_elapsed = convert_time(&clock) - *time_elapsed;

            if (!WIFEXITED(status)){

                perror("son bad termination");
                _exit(1);
            }

            printf(MAG "Ended in %lld ms\n" RESET, *time_elapsed);
            fflush_command(command,p);
            fflush(stdout);

            break;
    }

    return 0;
}