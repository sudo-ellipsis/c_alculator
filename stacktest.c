#include<stdlib.h>
#include<stdio.h>
#include"stack.h"

int main(void){
    Stack_t* stack = st_createStack();
    int i;

    printf("Stack length: %d\n",st_length(stack));
    for(i=0;i<10;i++){
        int* value = malloc(sizeof(int));
        *value = i;
        st_push(stack,value);
    }
    printf("Stack length: %d\n",st_length(stack));
    printf("Current top: %d\n",*((int*)st_peek(stack)));
     for(i=0;i<10;i++){
        printf("Popped stack! Value returned: %d\n",*((int*)st_pop(stack)));
    }

    st_deleteStack(stack);
    


    return 0;
}