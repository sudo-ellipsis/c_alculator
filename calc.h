#ifndef CALC_H
#define CALC_H


/* directions */
#define LEFT_ASSOCIATIVE 0
#define RIGHT_ASSOCIATIVE 1

/* operator definitions */
#define ADD '+'
#define SUB '-'
#define MULT '*'
#define DIV '/'
#define POW '^'
#define MOD '%'
#define COMMA ','
#define LBR '('
#define RBR ')'
#define SCIENTIFIC_NOT 'E'

/* data types */
#define INT "%d"
#define FLOAT "%f"
#define DOUBLE "%lf"

/* constants */
#define FALSE 0
#define TRUE 1
#define CONSTANT_COUNT 3
#define PI_ID "pi"
#define PHI_ID "phi"
#define EUL_ID "e"
#define PHI ((long double)1.61803398874989484820)
#define PI ((long double)3.141592653589793)
#define EUL ((long double)2.7182818285)

#define INPUT_BUFSIZE ((int)1023)

/* function definitions */
#define FUNCTION_COUNT 20
#define SIN "sin"
#define COS "cos"
#define TAN "tan"
#define LOG10 "log"
#define LOGE "ln"
#define ABS "abs"
#define FLOOR "floor"
#define ROUND "round"
#define CEIL "ceil"
#define ARCSIN "asin"
#define ARCCOS "acos"
#define ARCTAN "atan"
#define SQRT "sqrt"
#define CBRT "cbrt"
#define TORAD "toRad"
#define TODEG "toDeg"
#define FACTORIAL "factorial"
#define INVERT_N "n"
#define INVERT_M "m"
#define INVERT_UNDERSCORE "_"

/* custom datatypes */
typedef enum{
    integer,
    decimal,
    operator,
    function,
    invalid
} Type;

typedef struct{
    char* value;
    Type type;
} Token_t;

typedef long double (*mathFn)(long double);


#endif