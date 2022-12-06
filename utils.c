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
#include"__math.h"

int isAlphabeticalChar(char ch){
    return (strchr("abcdefghijklmnopqrstuvwxyzABCDFGHIJKLMNOPQRSTUVWXYZ_",ch) != NULL); /* no capital E, it's reserved as the scientific operator */
}

int isDigit(char ch){
    return (strchr("1234567890.",ch) != NULL);
}

int isOperand(char ch){
    char operands[] = {ADD,SUB,MULT,DIV,POW,MOD,SCIENTIFIC_NOT};
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
    char* validFunctions[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, EXP, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT,TORAD, TODEG, FACTORIAL, INVERT_N, INVERT_M, INVERT_UNDERSCORE};
    for(i=0;i<FUNCTION_COUNT;i++){
        if(strcmp(validFunctions[i],str) == 0){
            retval = TRUE;
        }
    }
    return retval;
}

int isConstant(char* str){
   int i, retval = FALSE;
   char* constants[CONSTANT_COUNT] = {PI_ID,PHI_ID,EUL_ID};
   for(i=0;i<2;i++){
        if(strcmp(constants[i],str) == 0){
            retval = TRUE;
        }
    }
    return retval;
}

double getConstantValue(char* str){ 
    /* we can assume that there is no required match fail return value, 
    as it is guaranteed to be a constant (uses same list as isConstant) */
    int i;
    double db;
    char* constants[CONSTANT_COUNT] = {PI_ID,PHI_ID,EUL_ID};
    double constantValues[CONSTANT_COUNT] = {PI,PHI,EUL};
    for(i=0;i<CONSTANT_COUNT;i++){
        if(strcmp(str,constants[i])==0){
            db = constantValues[i];
        }
    }
    return db;
}


int opPrecedence(char op){
    int prec;
    switch(op){ /* B I M D A S */
        case SCIENTIFIC_NOT:
            prec = 5; /* bodge scientific notation numbers to the top, 
                        as they're not actually a "rea" operator, but are
                        meant to denote a number - evaluating them takes priority*/
            break;
        case LBR:
        case RBR:
            prec=4;
            break;
        case POW:
            prec = 3;
            break;
        case MULT:
        case DIV:
        case MOD:
            prec = 2;
            break;
        case ADD:
        case SUB:
            prec = 1;
            break;
    }
    return prec;
}

void raiseError(char* errorMsg,char* badValue){
    printf("Error: %s at position %s\n",errorMsg,badValue);
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
        case SCIENTIFIC_NOT:
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
        } else if(isConstant(token)) {
            retval = decimal;
        } /* otherwise it's invalid */
    } else if(isNumeric(token)){
        retval = getNumericDatatype(token);
    } else if(isOperand(token[0])){
        retval = operator;
    }
    return retval;
}

long double getDoubleOfNumeric(char* value,Type type){
    long double db;
    if(isConstant(value)){
        db = getConstantValue(value);
    } else {
        if (type == integer){
            int i;
            sscanf(value,"%d",&i);
            db = (long double)i;
        } else {
            sscanf(value,"%Lf",&db);
        }
    }
    return db;
}

long double degToRad(long double angle){
    return angle * PI/180;
}

long double radToDeg(long double angle){
    return angle * 180 / PI;
}

long double factorial(long double x){
    return tgammal(x+1);
}

long double pow10(long double x){
    if(x < 0){ /* stupid off by one where pow (10,-2) == 0.1 */
        x--;
    }
    return powl(10,x);
}

long double invert(long double x){
    return -1 * x;
}