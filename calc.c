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

void printHelp(void){
    printf(
    "calc - a simple C calculator by ellipsis (@sudo-ellipsis, ellipsis#1984)\n"
    "--------------------------------------------------------\n"
    "IMPORTANT NOTES:\n"
    "All trigonometric calculations take radians\n"
    "All non operator or alphabetical characters will be discarded\n"
    "All values are calculated as doubles\n"
    "To express scientific notation, use a large \x1b[32mE\033[39m (1\x1b[32mE\033[39m3 == 1000)\n"
    );
    printf(
    "Negative numbers are expressed using \x1b[32m_\033[39m, \x1b[32mn\033[39m or \x1b[32mm\033[39m (\x1b[32m_\033[39m3\x1b[32m^\033[39m == 9)\n"
    );
    printf(
    "VALID OPERATORS:\n"
    "\x1b[32m+\033[39m, \x1b[32m-\033[39m, \x1b[32m*\033[39m, \x1b[32m/\033[39m,\x1b[32m %%\033[39m, \x1b[32m^\033[39m\n"
    "The power operator [\x1b[32m^\033[39m] is right associative (2\x1b[32m^\033[39m2\x1b[32m^\033[39m3 == 256)\n"
    );
    printf(
    "VALID FUNCTIONS:\n"
    "All functions take exactly one argument\n"
    "\x1b[32msin\033[39m(), \x1b[32mcos\033[39m(), \x1b[32mtan\033[39m()\n"
    "\x1b[32masin\033[39m(), \x1b[32macos\033[39m(), \x1b[32matan\033[39m()\n"
    "\x1b[32mtoRad\033[39m(), \x1b[32mtoDeg\033[39m()\n"
    "\x1b[32mround\033[39m(), \x1b[32mfloor\033[39m(), \x1b[32mceil\033[39m()\n"
    );
    printf(
    "\x1b[32mlog\033[39m() [base 10], \x1b[32mln\033[39m() [base e], \x1b[32mexp\033[39m() [base e]\n"
    "\x1b[32mabs\033[39m(), \x1b[32msqrt\033[39m(), \x1b[32mcbrt\033[39m(), \x1b[32mfactorial\033[39m()\n"
    "VALID CONSTANTS:\n"
    "\x1b[32mpi\033[39m, \x1b[32mphi\033[39m, \x1b[32me\033[39m\n"
    "--------------------------------------------------------\n"
    );
    return;
}

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
            printf("%-.16g\n",getDoubleOfNumeric(result->value,result->type));
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
                        printf("\033[1;35m%-.16g\033[39m\n",getDoubleOfNumeric(result->value,result->type));
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