#include <stdio.h>
#include <stdlib.h>
#include "extern_ dependency/hashtable.h"

typedef struct {
    int* offset;
    void* local_var;
}stack_slot;

void* get_local_var_value(stack_slot* slot, int index, void* value){
    int i = slot->offset[index];
    void* position = slot->offset + i;
    return position;
}

void set_local_var_value(stack_slot* slot, int index, void* value){
    int i = slot->offset[index];
    void* position = slot->offset + i;
    for (int j = 0; j < i; j++){
        *((char*) (position + j)) = *((char*) (value + j));
    }
}

stack_slot init_local_var(int num, int size){
    stack_slot slot;
    slot.offset = (int*) malloc(num * sizeof(int));
    slot.local_var = malloc(sizeof(size));
    return slot;
}

void destory_local_var(stack_slot* slot){
    free(slot->offset);
    free(slot->local_var);
}

typedef struct {
    stack_slot local_var_array;
    void* operate_stack;
    
}stack_frame;

void push(int index){
    printf("%d\n", index);
}



int main(int argc, char **argv){

    
}