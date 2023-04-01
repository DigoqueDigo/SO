#include <files.h>


void save_package(char *path, PACKAGE package){

    int fd;
    char filemane[FILENAME_SIZE];
    strcpy(filemane,path);

    get_filename(filemane,get_package_pid(package));

    switch (fork()){

        case -1:
            perror("fork");
            _exit(1);

        case 0:

            fd = open(filemane, O_CREAT | O_RDWR, 0666);

            if (fd == -1){

                perror("open");
                _exit(1);
            }

            if (write(fd,&package,sizeof(package)) == -1){

                perror("write");
                _exit(1);
            }

            close(fd);
            _exit(0);
    }
}


void show_package(char *path, int pid){

    PACKAGE package;
    int fd;
    char filemane[FILENAME_SIZE];
    ssize_t bytes;

    strcpy(filemane,path);
    get_filename(filemane,pid);

    fd = open(filemane, O_RDONLY, 0666);

    if (fd == -1) _exit(1);

    bytes = read(fd,&package,sizeof(package));

    if (bytes != sizeof(package)){

        perror("read");
        _exit(1);
    }

    print_package(package);
    close(fd);
}