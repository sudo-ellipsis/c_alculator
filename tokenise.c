/* standard includes */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* extern includes */
#include"stack.h"
#include"calc.h"
#include"utils.h"

Stack_t* tokenise(char* str){
     Stack_t* tokenOutput = st_createStack();
    int currentChar,bufLength;
    char token;
    char* data;
    char* buf = malloc(INPUT_BUFSIZE + 1 * sizeof(char)); /* buffer for token building*/
    for(currentChar=0;currentChar<((int)strlen(str));currentChar++){
        memset(buf,0,INPUT_BUFSIZE + 1); /* zero buffer */
        token = str[currentChar];
        bufLength=0; /* reset buffer index */
        if(!isIgnorable(token)){
            if(isAlphabeticalChar(token)){ /* if regular char */
                while(isAlphabeticalChar(token) && bufLength < (int)strlen(str) && !isFunction(buf) &&!isConstant(buf)){ /* while chars read are alphabetical */
                    buf[bufLength] = token; /* write token to buffer */
                    currentChar++; /* advance one character in input string */
                    bufLength++; /* advance to next buffer address */
                    token = str[currentChar]; /* update token */  
                }
                currentChar--; /* avoid over-increment */
                data = malloc((bufLength + 1) * sizeof(char)); /* allocate memory for token w/ nullptr space */
                memcpy(data,buf,bufLength + 1); /* copy relevant data from buffer */
                st_push(tokenOutput,data); /* push token to stack */
            } else if(isDigit(token)){ /* basically the same as alphabetical */
                while(isDigit(token) && currentChar < (int)strlen(str)){ /* while chars read are digits */
                    buf[bufLength] = token; /* write token to buffer */
                    currentChar++; /* advance one character in input string */
                    bufLength++; /* advance to next buffer address */
                    token = str[currentChar]; /* update token */
                }
                currentChar--; /* avoid over-increment */
                data = malloc((bufLength + 1) * sizeof(char)); /* allocate memory for token w/ nullptr space */
                memcpy(data,buf,bufLength + 1); /* copy relevant data from buffer */
                st_push(tokenOutput,data); /* push token to stack */
            } else if(isOperand(token) || token == RBR || token == LBR){
                data = calloc(2,sizeof(char)); /* zero byes - it's a single char string, so the second is kept as null term */
                data[0] = token;
                st_push(tokenOutput,data);
            }
        }  
    }

    tokenOutput = st_reverseStack(tokenOutput);
    free(buf);
    return tokenOutput;
}

int test(int argc, char** argv){
    char* data;
    char* input = "400 + 200*sin(12.53012) - 1/2 + max(3*sin(5),5*sin(3)) - 3!^sqrt(7)";
    Stack_t* tokens;

    if(argc > 1){
        input = argv[1];
    }

    tokens = tokenise(input);

    printf("Tokens:\n[");
    while(!st_isEmpty(tokens)){
        data = (char*)st_pop(tokens);
        printf("%s",data);
        free(data);
        if(!st_isEmpty(tokens)){
            printf(" ");
        }
    }
    printf("]\n");

    return 0;
}