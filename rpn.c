/* standard includes */
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* extern includes */
#include"calc.h"
#include"stack.h"
#include"utils.h"

Stack_t* rpn(Stack_t* tokens){ /* uses shunting yard to translate a token list from standard notation to reverse polish */
    Stack_t* operatorStack = st_createStack(); /* create op stack */
    Stack_t* outputStack = st_createStack(); /* output stack */
    char* token;
    char op;

    while(!st_isEmpty(tokens)){ /* while tokens exist */
        token = (char*)st_pop(tokens); /* read token */
        if(isNumeric(token)){ /* if token is numeric */
            st_push(outputStack,token); /* push it onto output */
        } else if (isAlphabetical(token)){ /* if function */
            st_push(operatorStack,token);
        } else if(strlen(token) == 1 && isOperand(token[0])) { /* if op */
            if(!st_isEmpty(operatorStack)){
                op = (*((char*)st_peek(operatorStack))); /* get top operator - single char*/
                while( !st_isEmpty(operatorStack) && (op != LBR && (isOperand(op) || op == RBR)) && ((opPrecedence(op) > opPrecedence(token[0])) || (opPrecedence(op) == opPrecedence(token[0]) && isLeftAssociative(token[0])) ) ){/* while operator is either rbr or an operator with either higher precedence or same with left associative token  */
                    st_push(outputStack,st_pop(operatorStack)); /* pop top operator to output queue */
                    if(!st_isEmpty(operatorStack)){
                        op = (*((char*)st_peek(operatorStack))); /* get top operator - single char*/
                    }
                }
            }
            st_push(operatorStack,token); /* push token to op stack */
        } else if (strlen(token) == 1 && token[0] == LBR) { /* if left bracket */
            st_push(operatorStack,token); /* push onto op stack */
        } else if (strlen(token) == 1 && token[0] == RBR) { /* if right bracket */
            op = *((char*)st_peek(operatorStack));
            while(op != LBR){ /* pop all operators until left bracket found */
                if(st_isEmpty(operatorStack)){
                    raiseError("Mismatched parenthesis! Right parenthesis with no match!\n",st_peek(tokens));
                }
                st_push(outputStack,st_pop(operatorStack)); /* push from op stack to output */
                op = *((char*)st_peek(operatorStack));
            }
            if(strlen((char*)st_peek(operatorStack)) != 1 && *((char*)st_peek(operatorStack)) != LBR){
                raiseError("Mismatched parenthesis! No left parenthesis at stack top!\n",st_peek(tokens));
            } else {
                st_pop(operatorStack); /* discard the left parenthesis */
            } 
            if(isAlphabetical(st_peek(operatorStack))){ /* if top of op stack is a function */
                st_push(outputStack,st_pop(operatorStack)); /* move it to output stack */
            } else {
            }
        } else {
            raiseError("Token Ignored! Token provided was not numeric, alphabetical, operand or bracket).\n",token);
        }
    }
    while(!st_isEmpty(operatorStack)){ /* while tokens are on operator stack */
        if(strlen((char*)st_peek(operatorStack)) != 1 && *((char*)st_peek(operatorStack)) == LBR){ /* check if there's a left bracket */
                    raiseError("Mismatched parenthesis! Left parenthesis at operator stack top after final token!\n",st_peek(operatorStack));
        }
        st_push(outputStack, st_pop(operatorStack)); /* move the tokens over */   
    }
    st_deleteStack(operatorStack);
    return outputStack; /* the output is reversed from regular RPN */
}
