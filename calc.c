/* standard includes */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* extern includes */
#include"calc.h"
#include"rpn.h"
#include"stack.h"
#include"tokenise.h"
#include"eval.h"

int main(void){
    char *input = calloc((INPUT_BUFSIZE + 1),sizeof(char));
    Token_t* result;
    
    while(strcmp(input,"EXIT") != 0){
        printf("Enter an expression, or type EXIT to exit\n>");
        if(fgets(input,INPUT_BUFSIZE,stdin)){ /* read something */
            input[strcspn(input,"\n")] = '\0'; /* turn the newline into a null term */
            printf("Input: \"%s\"\n",input);
            if(strcmp(input,"EXIT") != 0){ /* check for EXIT string */
                result = evaluateRPN(rpn(tokenise(input)));
                printf("Result: %s\n",result->value);
                free(result->value);
                free(result);
            } else {
                printf("Exiting...\n");
            }
        } else { /* if no input registered */
            printf("Input must not be empty!\n");
        }
    }  

    free(input);
    return 0;
}