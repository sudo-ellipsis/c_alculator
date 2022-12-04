/* 
Every utility used throughout the program
Mostly just short flexible utilities (e.g, is a given string numeric)
*/

/* standard includes */
#include<math.h>
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
    char operands[] = {ADD,SUB,MULT,DIV,POW,MOD};
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
    int i,retval = FALSE;
    char* validFunctions[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, EXP, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT,TORAD, FACTORIAL};
    for(i=0;i<FUNCTION_COUNT;i++){
        if(strcmp(validFunctions[i],str) == 0){
            retval = TRUE;
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
            retval = FALSE;
            break;
    }
    return retval;
}

Type getNumericDatatype(char* token){ /* for numerics */
    int i = 0;
    int pointCount = 0;
    Type retval;
    if(strchr("1234567890",token[0]) != NULL){ /* first digit must be number*/
        for(i=0;i<(int)strlen(token);i++){
            if(token[i] == '.'){ /* if there's a decimal point */
                pointCount++;
            }
        }
        if(pointCount == 1){
            retval = decimal;
        } else if(pointCount==0){
            retval = integer;
        } else {
            retval = invalid;
        }
    } else {
        retval = invalid;
    }
    return retval;
}

Type getTokenDatatype(char* token){
    Type retval = invalid;
    if(isAlphabetical(token)){
        if(isFunction(token)){
            retval = function;
        } /* otherwise it's invalid */
    } else if(isNumeric(token)){
        retval = getNumericDatatype(token);
    } else if(isOperand(token[0])){
        retval = operator;
    }
    return retval;
}

double getDoubleOfNumeric(char* value,Type type){
    double db;
    if (type == integer){
        int i;
        sscanf(value,"%d",&i);
        db = (double)i;
    } else {
        sscanf(value,"%lf",&db);
    }
    return db;
}

double degToRad(double angle){
    return angle * PI/180;
}

double tgamma(double);
double factorial(double x){
    return tgamma(x++);
}