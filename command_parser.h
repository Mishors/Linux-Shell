#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H
#include <stdio.h>
/*
	- This function should be responsible for importing all details of the command
	- Should specify the type of the command "comment, cd, echo, expression - X=5 -, else"
	- Should specify the arguments of the command
	- Should specify if the command is background or foreground
	- Should consider all parsing special cases, example: many spaces in  "ls     -a"
	- You're left free to decide how to return your imported details of this command
	- Best practice is to use helper function for each collection of logical instructions,
	  example: function for splitting the command by space into array of strings, ..etc
*/
char ** parse_commands(char* command);

char * read_in();

char * read_File(FILE *fp);

int isAssign(char* command);

int isDelimiter(char c);

int isDelimVar(char c);

//void assign_ (char* command,char** varTab);

char ** getPaths(char* command, char*PATH);

char* filterCommand (char* command,char** varTab);

#endif // COMMAND_PARSER_H
