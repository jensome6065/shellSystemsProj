compile shell.out: main.o parse.o cd.o exit.o pipes.o redirect.o err.o 
	@gcc -o shell.out main.o parse.o cd.o exit.o pipes.o redirect.o err.o 
run: shell.out
	@./shell.out
main.o: main.c parse.h cd.h exit.h pipes.h redirect.h err.h 
	@gcc -c main.c 
parse.o: parse.c 
	@gcc -c parse.c
cd.o: cd.c 
	@gcc -c cd.c
exit.o: exit.c 
	@gcc -c exit.c
redirect.o: redirect.c
	@gcc -c redirect.c
pipes.o: pipes.c 
	@gcc -c pipes.c
err.o: err.c 
	@gcc -c err.c
clean:
	@rm -f *.o
	@rm -f *.out
	@rm -f shell.out