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
#include"utils.h"
int main(int argc, char** argv){
    char *input = calloc((INPUT_BUFSIZE + 1),sizeof(char));
    Token_t* result;

    if(argc > 1){
        int i;
        for(i=1;i<argc;i++){
            strcat(input,argv[i]);
        }
        if(strcmp(input, "HELP") ==0){
            printHelp();
        } else {
            result = evaluateRPN(rpn(tokenise(input)));
            printf("%-10.10Lg\n",getDoubleOfNumeric(result->value,result->type));
            free(result->value);
            free(result);
        }
    } else {
        printf("Enter an expression, type HELP for help, or type EXIT to exit\n");
        while(strcmp(input,"EXIT") != 0){
            if(fgets(input,INPUT_BUFSIZE,stdin)){ /* read something */
                input[strcspn(input,"\n")] = '\0'; /* turn the newline into a null term */
                if(strcmp(input, "HELP") ==0){
                    printHelp();
                } else if(strcmp(input,"EXIT") != 0){ /* check for EXIT string */
                    /* printf("Evaluating [%s]\n",input); */
                    result = evaluateRPN(rpn(tokenise(input)));
                    if(result->type == decimal || result->type == integer){
                        printf("\033[1;35m%-10.10Lg\033[39m\n",getDoubleOfNumeric(result->value,result->type));
                    } else {
                        printf("\033[1;31mNaN\033[39m\n");
                    }
                    
                    free(result->value);
                    free(result);
                } else if(strcmp(input,"HELP")==0){
                    printHelp();
                }
                else {
                    printf("Exiting...\n");
                }
            } else { /* if no input registered */
                printf("Input must not be empty!\n");
            }
        }
    }

    free(input);
    return 0;
}