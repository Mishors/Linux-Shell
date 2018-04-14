#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //exec
#include "command_parser.h"
#include "commands.h"
#include "environment.h"
#include "execution.h"
#include <string.h>
#include <assert.h>

char* varTab[500];



int main(int argc, char *argv[])
{
   argc--;

   char ** varTab;

   varTab = setup_environment();

   char *input ;

   char *filter ;

   char **command ;

   FILE *batch,*history,*history2;

   history = fopen(strcat(varTab[3],"/historyFile"),"a");


   if(argc == 1){
    batch = fopen(argv[1], "r");
   }//if

   while(1){
    START:;
    if(argc == 0){
     printf("Shell> ");
     input  = read_in();
     }
    else{
     input  = read_File(batch);
     }
    fputs(input,history);
    if(isComment(input))
     goto START;
    if(isAssign(input)){
      assign_(input,varTab);
     }//if

    filter = filterCommand(input,varTab);
    command = parse_commands(filter);
    int k=0;
    int cnt = 2;
    if(isHistory(command)){
     continue;
    }//if
    int isBack = isBackground(command);
    if(isBack){
     command = removeAnd(command);
    }//if
    int exit = execute(input,command,varTab,isBack);
    if(exit){
     break;
    }//if

   }//while
    if(argc ==1){
       fclose(batch);
    }//if

    fclose(history);



    return 0;
}
