#include <files.h>


void save_package(char *path, PACKAGE package){

    int fd;
    char *filename = get_filename(path,get_package_pid(package));

    fd = open(filename, O_CREAT | O_RDWR, 0666);

    if (fd == -1){

        perror("open");
        _exit(1);
    }

    if (write(fd,&package,sizeof(PACKAGE)) == -1){

        perror("write");
         _exit(1);
    }

    close(fd);
    free(filename);
}


void show_package(char *path, int pid){

    int fd;
    ssize_t bytes;
    PACKAGE package;
    char *filename = get_filename(path,pid);

    fd = open(filename, O_RDONLY, 0666);

    if (fd == -1) _exit(1);

    bytes = read(fd,&package,sizeof(PACKAGE));

    if (bytes != sizeof(PACKAGE)){

        perror("read");
        _exit(1);
    }

    print_package(package);
    free(filename);
    close(fd);
}