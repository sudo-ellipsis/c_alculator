#ifndef EVAL_H
#define EVAL_H

mathFn findMathFn(char* functionName);
Token_t* doOperation(Token_t* operand, Token_t* firstValue, Token_t* secondValue);
Token_t* doFunction(Token_t* function, Token_t* arg);
Token_t* evaluateRPN(Stack_t* tokens);

#endif