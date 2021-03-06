#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


stack_slot init_local_var(int num, int size, int* index){
    stack_slot slot;
    slot.offset = (int*) malloc(num * sizeof(int));
    for (int i = 0; i < num; i++){
        slot.offset[i] = index[i];
    }
    slot.local_var = malloc(sizeof(size));
    return slot;
}
void destory_local_var(stack_slot* slot){
    free(slot->offset);
    free(slot->local_var);
}

void* get_local_var_value(stack_slot* slot, int index){
    int i = slot->offset[index];
    void* position = slot->local_var + i;
    return position;
}

void set_local_var_value(stack_slot* slot, int index, void* value, int length){
    int i = slot->offset[index];
    void* position = slot->local_var + i;
    if (length == 8){
        *(void**)position = value;
    }else{
        for (int j = 0; j < length; j++){
            *((char*) (position + j)) = *((char*) (value + j));
        }
    }
    
}

operate_stack init_operate_stack(int size){
    operate_stack os;
    os.size = size;
    os.count = 0;
    os.stack = malloc(size);
    os.header = os.stack;
    return os;
}

void destory_operate_stack(operate_stack* os){
    free(os->header);
}

void push_operate_stack_int(operate_stack* os, int value){
    *((int*)os->stack) = value;
    os->stack = os->stack + sizeof(int);
    os->count = os->count + 1;
}

int pop_operate_stack_int(operate_stack* os){
    os->stack = os->stack - sizeof(int);
    int i = *(int*)(os->stack);
    os->count = os->count - 1;
    return i;
}

void push_operate_stack_char(operate_stack* os, char c){
    *((char*)os->stack) = c;
    os->stack = os->stack + sizeof(char);
    os->count = os->count + 1;
}

int add_int(operate_stack* os){
    os->stack = os->stack - sizeof(int);
    int i = *(int*)(os->stack);
    os->count = os->count - 1;
    os->stack = os->stack - sizeof(int);
    int j = *(int*)(os->stack);
    os->count = os->count - 1;
    return i + j;
}

char add_char(operate_stack* os){
    os->stack = os->stack - sizeof(char);
    char i = *(char*)(os->stack);
    os->count = os->count - 1;
    os->stack = os->stack - sizeof(char);
    char j = *(char*)(os->stack);
    os->count = os->count - 1;
    return i + j;
}

stack_frame init_stack_frame(int operate_stack_size, int local_var_num, int local_var_size, int* index){
    stack_frame sf;
    sf.local_var_array = init_local_var(local_var_num, local_var_size, index);
    sf.os = init_operate_stack(operate_stack_size);
    return sf;
}

void push_operate_stack_object(operate_stack* os, void* value){
    *(void**)os->stack = value;
    os->stack = os->stack + sizeof(void*);
    os->count = os->count + 1;
}
void* pop_operate_stack_object(operate_stack* os){
    os->stack = os->stack - sizeof(void*);
    void* object = *(void**)os->stack;
    os->count = os->count - 1;
    return object;
}


