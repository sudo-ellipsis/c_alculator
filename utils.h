#ifndef UTILS_H
#define UTILS_H

int isIgnorable(char ch);
int isOperand(char ch);
int isDigit(char ch);
int isAlphabeticalChar(char ch);
int isNumeric(char* str);
int isAlphabetical(char* str);
int isFunction(char* str);
int opPrecedence(char op);
int isLeftAssociative(char op);
void raiseError(char* errorMsg,char* badValue);
#endif