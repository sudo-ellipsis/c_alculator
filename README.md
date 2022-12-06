# C-alculator - A C command line calculator

A simple C calculator I made for fun using that tokenises a mathematical input, then uses a slightly modified [shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm) to generate [reverse polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) from it, which is then simply evaluated.

Made using c89 for linux, as that's what I'm used to. Supports a variety of functions and operators - the help command further details these. Also supports command line arguments, however it's more finicky as bash will tend to pick up many mathematical characters.

Likely error prone with unexpected input, but I've done my best to sort out edge cases and memory leaks with strange cases.

For more information, run `./calc HELP`



## Building
```bash
make
make clean
./calc
```

## Simplified program structure
The program works with 'tokens' in stacks - first with simple `char*`'s, then with `Token_t*`'s that detail the type of `char*`.
First, the input is passed to the tokenizer. This reads in characters one by one, matching either patterns of digit [0-9, .], operator, or alphabetical patterns. If the sequence of like characters ends, or in the case of functions/constants, matches a valid name, it's split into its own token. This stack is then returned.

Then, the RPN is generated using the shunting yard algorithm. To simplify, this uses an operator and output stack, shifting values to output and sorting operators/functions based on their precedence, associativity, and position within brackets. A special case is added for negative numbers, which are appended to the next possible value.

This ordered notation is then evaluated using eval.c. This involves assigning a type to each token, then reversing the whole stack into reverse polish notation (as RPN is meant to provide a queue, but it is returned in a stack, the stack gets reversed to change from LIFO to FIFO). Then, value tokens are put to output, and taken off when operators or functions are encountered to be modified. The final value is returned.

Unless a mathematical operation is done, the token values are kept as `char*`, as this allows one datatype to handle numerics and operations.

## Functions and operators supported
### Functions
All functions take a single input.
Brackets are not required for function calls (for example, negation is a bracket less function call), however a lack of brackets may lead to unexpected output. 
Negation does not require a bracket, as it is always associated with the next value. (`_3^2` will return `9`)

Trigonometric functions: `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`

Conversions: `toRad()`, `toDeg()`

Rounding: `round()`, `ceil()`, `floor()`

Powers: `log()` [base 10], `ln()`

Other: `abs()`, `sqrt()`, `cbrt()`, `factorial()`

Negation: `_`, `n`, `m`.

### Operators
Addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), modulo (`%`), power (`^`), scientific notation (`E`)

### Constants
`e`, `pi`, and `phi` are all their expected values to a fair amount of decimal places
