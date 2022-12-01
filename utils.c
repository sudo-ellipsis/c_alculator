/* standard includes */
#include<string.h>
#include<stdio.h>
/* extern includes */
#include"calc.h"

int isAlphabeticalChar(char ch){
    return (strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",ch) != NULL);
}

int isDigit(char ch){
    return (strchr("1234567890.",ch) != NULL);
}

int isOperand(char ch){
    char operands[] = {ADD,SUB,MULT,DIV,POW, MOD, FACTORIAL};
    return (strchr(operands,ch) != NULL);
}

int isIgnorable(char ch){
    return (!isAlphabeticalChar(ch) && !isDigit(ch) && !isOperand(ch) && ch != RBR && ch != LBR);
}

int isNumeric(char* str){
    int i,retval = TRUE;
    for(i=0;i<(int)strlen(str);i++){
        if(!isDigit(str[i])){
            retval=FALSE;
        }
    }
    return retval;
}

int isAlphabetical(char* str){
    int i,retval = TRUE;
    for(i=0;i<(int)strlen(str);i++){
        if(!isAlphabeticalChar(str[i])){
            retval=FALSE;
        }
    }
    return retval; 
}

int isFunction(char* str){
    int i,retval = 1;
    char* validFunctions[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, EXP, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT};
    for(i=0;i<FUNCTION_COUNT;i++){
        if(strcmp(validFunctions[i],str) == 0){
            retval = 0;
        }
    }
    return retval;
}

int opPrecedence(char op){
    int prec;
    switch(op){ /* B I M D A S */
        case POW:
            prec = 4;
            break;
        case MULT:
        case DIV:
        case MOD:
            prec = 3;
            break;
        case ADD:
        case SUB:
            prec = 2;
            break;
    }
    return prec;
}

void raiseError(char* errorMsg,char* badValue){
    printf("Error: %s\nAdditional information: %s\n",errorMsg,badValue);
    return;
}

int isLeftAssociative(char op){
    int retval;
    switch(op){
        case MULT:
        case DIV:
        case MOD:
        case ADD:
        case SUB:
        case COMMA:
        case RBR:
        case LBR:
            retval = TRUE;
            break;
        case POW: /* assuming power is right associative */
        case FACTORIAL:
            retval = FALSE;
            break;
    }
    return retval;
}