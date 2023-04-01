#include <package/list.h>


LIST init_list(){

    LIST new = malloc(sizeof(struct list));

    new->list = malloc(INIT_SIZE*sizeof(PACKAGE));
    new->size = INIT_SIZE;
    new->sp = 0;

    return new;
}


void add_package(LIST list, PACKAGE package){

    if (list->sp >= list->size){

        list->size *= 2;
        list->list = realloc(list->list,list->size*sizeof(PACKAGE));
    }

    list->list[list->sp++] = package;
}


void remove_package(LIST list, int index){

    if (index >= 0 && index < list->sp){

        list->sp--;

        for (; index < list->sp; index++){

            list->list[index] = list->list[index+1];
        }
    }
}


int get_list_size(LIST list){

    return list->sp;
}


PACKAGE get_pakage(LIST list, int index){

    return list->list[index];
}


int get_index_pid(LIST list, int pid){

    for (int p = 0; p < list->sp; p++){

        if (list->list[p].pid == pid) return p;
    }

    return -1;
}


void print_list(LIST list){

    for (int p = 0; p < list->sp; p++){

        print_package(list->list[p]);
    }
}


void free_list(LIST list){

    free(list->list);
    free(list);
}
