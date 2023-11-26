compile shell.out: main.o parse.o funcs.o cd.o exit.o err.o pipes.o
	@gcc -o shell.out main.o parse.o funcs.o cd.o exit.o err.o pipes.o
run: shell.out
	@./shell.out
main.o: main.c parse.h funcs.h cd.h exit.h err.h pipes.h
	@gcc -c main.c 
parse.o: parse.c 
	@gcc -c parse.c
funcs.o: funcs.c 
	@gcc -c funcs.c
cd.o: cd.c 
	@gcc -c cd.c
exit.o: exit.c 
	@gcc -c exit.c
err.o: err.c 
	@gcc -c err.c
pipes.o: pipes.c 
	@gcc -c pipes.c
clean:
	rm -f *.o
	rm -f *.out
	rm -f shell.out