shell : main.o command_parser.o commands.o environment.o execution.o 
	gcc -o shell main.o command_parser.o commands.o \
	environment.o execution.o
main.o : main.c command_parser.h commands.h environment.h execution.h
	gcc -c main.c
command_parser.o : command_parser.c command_parser.h
	gcc -c command_parser.c
execution.o : execution.c execution.h commands.h
	gcc -c execution.c
commands.o : commands.c commands.h
	gcc -c commands.c
environment.o : environment.c environment.h
	gcc -c environment.c
clean : 
	rm main.o command_parser.o commands.o environment.o \
	execution.o 


