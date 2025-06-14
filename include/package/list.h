#ifndef LIST_H
#define LIST_H

#include <utils.h>
#include <package/package.h>

typedef struct list{
    PACKAGE *list;
    int sp;
    int size;
}*LIST;

LIST init_list();

void add_package(LIST list, PACKAGE package);

void remove_package(LIST list, int index);

PACKAGE get_pakage(LIST list, int index);

int get_list_size(LIST list);

int get_index_pid(LIST list, int pid);

void print_list(LIST list);

void free_list(LIST list);

#endif