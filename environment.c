#include "environment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char** setup_environment()
{    static char* out[512];
     const char *home ;
     char *value1 = malloc(500*sizeof(char));
	 home = "HOME";
     memcpy(value1,getenv(home),500*sizeof(char));
     const char *path ;
     char *value2 = malloc(500*sizeof(char));
	 path = "PATH";
     memcpy(value2,getenv(path),500*sizeof(char));

     out[0] = path;
     out[1] = value2;
     out[2] = home;
     out[3] = value1;
     out[4] = "$";

     return out;

}//method*/

void insertVar(char* key, char* value, char** tab){
int  i=0;

 while (strcmp(tab[i],"$")){

  if(!strcmp(tab[i],key)){
     tab[i+1] = value;
     return tab;
  }//if
  i++;
 }//while
 tab[i] = strdup(key);
 tab[i+1] = strdup(value);
 tab[i+2] = "$";

return ;
}//method

int isVariable(char* key,char ** tab){
int  i=0;
 while (strcmp(tab[i],"$")){
  if(!strcmp(tab[i],key)){
     return 1;//tab[i+1];
  }//if
  i++;
 }//while
 return 0;
}

int lookUp(char* key,char ** tab){
int  i=0;
 while (strcmp(tab[i],"$")){

  if(!strcmp(tab[i],key)){
     return i+1;//tab[i+1];
  }//if
  i++;
 }//while

}//method
