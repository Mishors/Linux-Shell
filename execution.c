#include "execution.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //exec
#include <signal.h>

int isBackground(char** command){
 int i=0;
 while (command[i] != NULL){
  i++;
 }//while
 if(!strcmp(command[i-1],"&")){
    return 1;
 }//if
 return 0;
}//method

char ** removeAnd(char ** command){
 int i=0;
 static char* out[512];
 out[0] = command[0];
 while (command[i+1] != NULL){
  out[i] = command[i];
  i++;
 }//while
 out[i] = NULL;
 return out;
}//method

void sighandler(int signum) {
    FILE *log;
    log = fopen("logFile","a");
    char msg[20];
    sprintf(msg, "Process %d terminated\n", signum);
    fputs(msg,log);
    fclose(log);
}//method

void sysCall (char** command,char** varTab,int isBackground){
    pid_t pid;
    int status;
    signal(SIGCHLD, sighandler);
    pid = fork();
    if (pid == 0){ /* child */
      char ** Paths = getPaths(command[0],varTab[1]);
      int i=0;
      //execvp(command[0],command);
      //printf("%s",Paths[0]);
      while (Paths[i] != NULL){
        execv(Paths[i],command);
        i++;
      }//while
       perror("Error: No such command");
    return;}
    else if (pid<0){
    perror("Error: During fork");

    } else{ /* parent */
      if(!isBackground){
        waitpid(pid, &status, 0);
        }
      }
    return;
}//method

int execute(char* line,char** command,char** varTab,int isBackground){
  int exitFlag = 0;

  if(command[0] == NULL){
   perror("Empty Command");
   return;
  }

  if(isAssign(line)){
     return 0;
   }//if

   if(isVariable(command[0],varTab)){
     printf("%s\n",varTab[lookUp(command[0],varTab)]);
     return 0;
   }

  if(!strcmp(command[0],"cd")){
    if(command[1] == NULL){
      return 0;
    }
    cd(command[1],varTab);
  }else if (!strcmp(command[0],"echo")){
    echo(command);
  }else if(!strcmp(command[0],"exit")){
    return 1; //exitFlag=1
  }else {
    sysCall(command,varTab,isBackground);
  }//else
  return exitFlag;
}//method
