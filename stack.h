#ifndef STACK_H
#define STACK_H

typedef struct StackMember_t{
    struct StackMember_t* next;
    void* data;
} StackMember_t;

typedef struct{
    StackMember_t* head;
    int length;
} Stack_t;

Stack_t* st_createStack();
int st_isEmpty(Stack_t* stack);
void st_push(Stack_t* stack, void* data);
void* st_pop(Stack_t* stack);
int st_length(Stack_t* stack);
void* st_peek(Stack_t* stack);
void st_deleteStack(Stack_t* stack);
Stack_t* st_reverseStack(Stack_t* stack);

#endif