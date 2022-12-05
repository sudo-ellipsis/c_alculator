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
    char* functionNames[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, EXP, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT,TORAD, TODEG, FACTORIAL, POW10};
    mathFn functions[FUNCTION_COUNT] = {&sin,&cos,&tan,&log10,&log,&fabs,&floor,&round,&ceil,&exp,&asin,&acos,&atan,&sqrt,&cbrt,&degToRad, &radToDeg, &factorial,&pow10};
    int i,fn;
    for(i=0;i<FUNCTION_COUNT;i++){
        if(strcmp(functionName,functionNames[i])==0){
            fn = i;
        }
    }
    return functions[fn];  
}

Token_t* signValue(Token_t* operand, Token_t* value){
    Token_t* result = malloc(sizeof(Token_t));
    double db;
    result->value = malloc(64*sizeof(char));
    switch(operand->value[0]){
        case '-':
            db = -1 * getDoubleOfNumeric(value->value,value->type);
            break;
        case '+':
            db = 1 * getDoubleOfNumeric(value->value,value->type);
            break;
    }
    result->type = decimal; /* set to double type */
    sprintf(result->value,"%f",db); /* convert back to string */
    free(operand->value);
    free(operand);
    free(value->value);
    free(value);
    return result;
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
    int isValid = TRUE;

    if(tokens->length == 0){ /* if there's no tokens */
        isValid = FALSE; /* it cannot be a valid expression */
        tk = calloc(1,sizeof(Token_t)); /* and we need to allocate a return token - we zero the bytes to ensure it's initialised */
    }

    /* link all tokens to a type and reverse them into a new stack */
    while(!st_isEmpty(tokens)){
        tk = malloc(sizeof(Token_t));
        tk->value = (char*)st_pop(tokens);
        tk->type = getTokenDatatype(tk->value);
        st_push(RPN,tk);
    }

    while(RPN->length > 0 && isValid){
        tk = (Token_t*)st_pop(RPN);
        /* printf("Validity at position %s: %d\n",tk->value,isValid); */
        if(tk->type == integer || tk->type == decimal){
            st_push(values,tk);
        } else if (tk->type == function){
            if(values->length >=1 ){
                st_push(values,doFunction(tk,st_pop(values)));
            } else {
                raiseError("Function mismatch! No arguments left for function",tk->value);
                isValid = FALSE;
            }   
        } else if (tk->type == operator){
            if(values->length >= 2){
                st_push(values,doOperation(tk,st_pop(values),st_pop(values)));
            } else if( tk->value[0] == '-'  && values->length >= 1){
                st_push(values,signValue(tk,st_pop(values)));
            } else {
                raiseError("Token mismatch! Not enough tokens for operator",tk->value);
                isValid = FALSE;
            }
            
        } else {
            raiseError("Invalid token type! Token was not recognised as an operator, function or value",tk->value);
            isValid = FALSE;
        }
    }

    if(!st_isEmpty(values)){
        tk = (Token_t*)st_pop(values);
    } 
    if(!isValid){
        tk->type = invalid;
    } 
    return tk;
}