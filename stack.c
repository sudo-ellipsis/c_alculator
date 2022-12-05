#include"stack.h"
#include<stdlib.h>

Stack_t* st_createStack(){ /* create new stack */
    Stack_t* stack = malloc(sizeof(Stack_t));
    stack->length = 0;
    stack->head = NULL;
    return stack;
} 

int st_isEmpty(Stack_t* stack){
    return (stack->length == 0);
}

void st_push(Stack_t* stack, void* data){ /* insert */
    StackMember_t* newMember = malloc(sizeof(StackMember_t));
    newMember->data = data;
    newMember->next = stack->head;
    stack->head = newMember;
    (stack->length)++;
    return;
}

void* st_pop(Stack_t* stack){ /* remove, return */
    void* headContent = stack->head->data;
    StackMember_t* oldHead = stack->head;
    if(stack->length > 0){
        stack->head = stack->head->next;
        (stack->length)--;
        free(oldHead);
    }
    return headContent;
}

int st_length(Stack_t* stack){
    return stack->length;
}

void* st_peek(Stack_t* stack){ /* return topmost */
    return stack->head->data;
} 

void st_deleteStack(Stack_t* stack){ /* recursively delete stack */
    while(!st_isEmpty(stack)){
        st_pop(stack);
    }
    free(stack);
    return;
}

Stack_t* st_reverseStack(Stack_t* stack){
    Stack_t* stackReversed = st_createStack();
      while(!st_isEmpty(stack)){ /* invert stack */
        st_push(stackReversed,st_pop(stack));
    }
    st_deleteStack(stack); /* delete old stack memory */
    return stackReversed; /* transfer over the reversed stack */
}

#ifdef NEVER_DEF
    void st_poke(Stack_t* stack); /* edit topmost value */ 
    void st_duplicate(Stack_t* stack); /* duplicate top */
    void st_swap(Stack_t* stack); /* swap topmost two */
    void st_rollDown(Stack_t* stack, int rollDepth); /* top to bottom */
    void st_rollUp(Stack_t* stack, int rollDepth); /* bottom to top */
#endif

