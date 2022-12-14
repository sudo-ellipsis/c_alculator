CFLAGS = -Wall -Werror -Wextra -ansi -pedantic -g
COMPILER = gcc
EXEC_NAME = calc
OBJ = calc.o rpn.o utils.o tokenise.o stack.o eval.o


$(EXEC_NAME): $(OBJ)
	$(COMPILER) $(CFLAGS) $(OBJ) -lm -o $(EXEC_NAME)

calc.o: calc.c calc.h rpn.h stack.h tokenise.h eval.h utils.h
	$(COMPILER) $(CFLAGS) calc.c -c

rpn.o: rpn.c calc.h stack.h utils.h 
	$(COMPILER) $(CFLAGS) rpn.c -c

utils.o: utils.c calc.h
	$(COMPILER) $(CFLAGS) utils.c -c

tokenise.o: tokenise.c calc.h stack.h utils.h
	$(COMPILER) $(CFLAGS) tokenise.c -c

stack.o: stack.c stack.h
	$(COMPILER) $(CFLAGS) stack.c -c

eval.o: eval.c calc.h utils.h stack.h
	$(COMPILER) $(CFLAGS) eval.c -c

clean: 
	rm -f $(OBJ) *.h.gch
