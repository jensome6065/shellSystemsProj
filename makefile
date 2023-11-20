compile shell.out: main.o parse.o funcs.o
	@gcc -o shell.out main.o parse.o funcs.o
run: shell.out
	@./shell.out
main.o: main.c parse.h funcs.h
	@gcc -c main.c 
parse.o: parse.c 
	@gcc -c parse.c
funcs.o: funcs.c 
	@gcc -c funcs.c
clean:
	rm -f *.o
	rm -f *.out
	rm -f shell.out