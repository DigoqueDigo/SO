#include <handle/status.h>


void handle_status(LIST list, PACKAGE package, int fifo[]){

    char *filename = get_filename("",get_package_pid(package));

    fifo[WRITE] = open(filename, O_WRONLY, 0666);

    if (fifo[WRITE] == -1){

        perror("open FIFO");
        _exit(1);
    }

    for (int p = 0; p < get_list_size(list); p++){

        package = get_pakage(list,p);
        set_package_timestamp(&package);

        if (write(fifo[WRITE],&package,sizeof(PACKAGE)) == -1){

            perror("write");
            _exit(1);
        }
    }

    free(filename);
    free_list(list);

    close(fifo[WRITE]);
    _exit(0);
}