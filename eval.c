/* standard includes */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* extern includes */
#include"calc.h"
#include"utils.h"
#include"stack.h"
#include"__math.h"


mathFn findMathFn(char* functionName){
    char* functionNames[FUNCTION_COUNT] = {SIN, COS, TAN, LOG10, LOGE, ABS, FLOOR, ROUND, CEIL, ARCSIN, ARCCOS, ARCTAN, SQRT, CBRT,TORAD, TODEG, FACTORIAL, INVERT_N, INVERT_M, INVERT_UNDERSCORE};
    mathFn functions[FUNCTION_COUNT] = {&sinl,&cosl,&tanl,&log10l,&logl,&fabsl,&floorl,&roundl,&ceill,&asinl,&acosl,&atanl,&sqrtl,&cbrtl,&degToRad, &radToDeg, &factorial, &invert, &invert, &invert};
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
    long double rVal, lVal, resultantVal; 
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
        case SCIENTIFIC_NOT:
            resultantVal = lVal * pow(10,rVal);
            break;
    }
    result->type = decimal; /* set to double type */
    sprintf(result->value,"%Lg",resultantVal); /* convert back to string */
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
    long double db = getDoubleOfNumeric(arg->value,arg->type); /* convert tokent to double */
    result->value = malloc(64*sizeof(char)); /* malloc space for the char - oversized */
    sprintf(result->value,"%Lg",findMathFn(function->value)(db)); /* evaluate function and reconvert to string */
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
    Token_t* tk_tmp; /* for freeing tokens on failure */
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
            } else {
                raiseError("Token mismatch! Not enough tokens for operator",tk->value);
                isValid = FALSE;
            }
            
        } else {
            raiseError("Invalid token type! Token was not recognised as an operator, function or value",tk->value);
            if(tk->value[0] == LBR || tk->value[0] == RBR){
                raiseError("Potential bracket mismatch!",tk->value);
            }
            isValid = FALSE;
        }
    }

    if(!st_isEmpty(values)){
        tk = (Token_t*)st_pop(values);
    } 
    if(!isValid || values->length > 0){ /* if the evaluation is invalid or there's more than one value on stack top it's invalid */
        tk->type = invalid;
    }

    /* free all tokens left in any stacks - tk is the only token that should remain*/
    while(!st_isEmpty(values)){ 
            tk_tmp = (Token_t*)st_pop(values);
            free(tk_tmp->value);
            free(tk_tmp);
    }
    while(!st_isEmpty(tokens)){
            tk_tmp = (Token_t*)st_pop(tokens);
            free(tk_tmp->value);
            free(tk_tmp);
    }
    while(!st_isEmpty(RPN)){
            tk_tmp = (Token_t*)st_pop(RPN);
            free(tk_tmp->value);
            free(tk_tmp);
    }

    st_deleteStack(values);
    st_deleteStack(tokens);
    st_deleteStack(RPN);
    return tk;
}