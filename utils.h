#ifndef UTILS_H
#define UTILS_H

int isIgnorable(char ch);
int isOperand(char ch);
int isDigit(char ch);
int isAlphabeticalChar(char ch);
int isNumeric(char* str);
int isAlphabetical(char* str);
int isFunction(char* str);
int isConstant(char* str);
long double getConstantvalue(char* str);
int opPrecedence(char op);
int isLeftAssociative(char op);
void raiseError(char* errorMsg,char* badValue);
Type getNumericDatatype(char* token);
Type getTokenDatatype(char* token);
long double getDoubleOfNumeric(char* value,Type type);
long double degToRad(long double angle);
long double radToDeg(long double angle);
long double factorial(long double x);
long double pow10(long double x);
long double invert(long double x);
void printHelp(void);

#endif