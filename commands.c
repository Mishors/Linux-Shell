#include "commands.h"
#include <stdlib.h>



void cd( char* path , char ** varTab)
{

    char *value;
    if(!strcmp(path,"~")){

     value = varTab[lookUp("HOME",varTab)];

     chdir(value);
    }else{
     chdir(path);
    }

}//method


void echo(char** message)
{
   int i=1;
   while (message[i] != NULL){
   printf("%s ",message[i]);
   i++;
   }
   printf("\n");
}//method
