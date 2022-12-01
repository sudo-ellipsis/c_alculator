/* standard includes */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* extern includes */
#include"calc.h"
#include"rpn.h"
#include"stack.h"
#include"tokenise.h"

int main(void){
    char* data;
    char *input = calloc((INPUT_BUFSIZE + 1),sizeof(char));
    Stack_t* parsedInput;
    
    while(strcmp(input,"EXIT") != 0){
        printf("Enter an expression, or type EXIT to exit\n>");
        if(fgets(input,INPUT_BUFSIZE,stdin)){ /* read something */
            input[strcspn(input,"\n")] = '\0'; /* turn the newline into a null term */
            printf("Input: \"%s\"\n",input);
            if(strcmp(input,"EXIT") != 0){ /* check for EXIT string */
                parsedInput = rpn(tokenise(input));
                printf("Tokens returned by RPN parser:\n[");
                    while(!st_isEmpty(parsedInput)){
                        data = (char*)st_pop(parsedInput);
                        printf("%s",data);
                        free(data);
                        if(!st_isEmpty(parsedInput)){
                            printf(" ");
                        }
                    }
                printf("]\n");
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