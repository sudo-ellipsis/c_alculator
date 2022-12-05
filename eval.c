/* standard includes */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* extern includes */
#include"calc.h"
#include"utils.h"
#include"stack.h"

double round(double);
double cbrt(double);

mathFn findMathFn(char* functionName){
    char* functionNames[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, EXP, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT,TORAD, TODEG, FACTORIAL};
    mathFn functions[FUNCTION_COUNT] = {&sin,&cos,&tan,&log10,&log,&fabs,&floor,&round,&ceil,&exp,&asin,&acos,&atan,&sqrt,&cbrt,&degToRad, &radToDeg, &factorial};
    int i,fn;
    for(i=0;i<FUNCTION_COUNT;i++){
        if(strcmp(functionName,functionNames[i])==0){
            fn = i;
        }
    }
    return functions[fn];  
}

Token_t* doOperation(Token_t* operand, Token_t* firstValue, Token_t* secondValue){
    Token_t* result = malloc(sizeof(Token_t));
    double rVal, lVal, resultantVal; 
    lVal = getDoubleOfNumeric(firstValue->value,firstValue->type); /* left value of expr */
    rVal = getDoubleOfNumeric(secondValue->value,secondValue->type); /* right value */
    result->value = calloc(64,sizeof(char)); /* large buffer */ 
    switch(operand->value[0]){ /* do operand */
        case ADD:
            resultantVal = lVal + rVal;
            break;
        case SUB:
            resultantVal = lVal - rVal;
            break;
        case MULT:
            resultantVal = lVal * rVal;
            break;
        case DIV:
            resultantVal = lVal / rVal;
            break;
        case POW:
            resultantVal = pow(lVal,rVal);
            break;
        case MOD:
            resultantVal = fmod(lVal,rVal);  
            break;
    }
    result->type = decimal; /* set to double type */
    sprintf(result->value,"%f",resultantVal); /* convert back to string */
    /* remove used tokens */
    free(operand->value);
    free(operand);
    free(firstValue->value);
    free(firstValue);
    free(secondValue->value);
    free(secondValue);
    return result;
}

Token_t* doFunction(Token_t* function, Token_t* arg){
    Token_t* result = malloc(sizeof(Token_t));
    double db = getDoubleOfNumeric(arg->value,arg->type); /* convert tokent to double */
    result->value = malloc(64*sizeof(char)); /* malloc space for the char - oversized */
    sprintf(result->value,"%f",findMathFn(function->value)(db)); /* evaluate function and reconvert to string */
    result->type = decimal; /* set type of value to double */

    /* free useless tokens */
    free(function->value); 
    free(function);
    free(arg->value); 
    free(arg);

    return result;
}

Token_t* evaluateRPN(Stack_t* tokens){
    Stack_t* RPN = st_createStack();
    Stack_t* values = st_createStack();
    Token_t* tk;

    /* link all tokens to a type and reverse them into a new stack */
    while(!st_isEmpty(tokens)){
        tk = malloc(sizeof(Token_t));
        tk->value = (char*)st_pop(tokens);
        tk->type = getTokenDatatype(tk->value);
        st_push(RPN,tk);
    }

    while(RPN->length > 0){
        tk = (Token_t*)st_pop(RPN);
        if(tk->type == integer || tk->type == decimal){
            st_push(values,tk);
        } else if (tk->type == function){
            st_push(values,doFunction(tk,st_pop(values)));
        } else if (tk->type == operator){
            st_push(values,doOperation(tk,st_pop(values),st_pop(values)));
        } else {
            raiseError("Invalid token type!",tk->value);
        }
    }
    return (Token_t*)st_pop(values);
}