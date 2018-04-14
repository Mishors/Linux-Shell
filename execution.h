#ifndef EXECUTION_H_INCLUDED
#define EXECUTION_H_INCLUDED

int isBackground(char** command);

char ** removeAnd(char ** command);

void sysCall (char** command,char** varTab,int isBackground);

int execute(char* line,char** command,char** varTab,int isBackground);

#endif // EXECUTION_H_INCLUDED
