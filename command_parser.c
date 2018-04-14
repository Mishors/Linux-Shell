#include "command_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int isAssign(char* command){
 int i=0;
 while(command[i] != NULL){
  if(command[i] == '='){
    return 1;
  }
  i++;
 }//while
 return 0;
}//method

int isDelimiter(char c){

   if(c == ' ' || c=='\t'  || c == '\r' || c=='\v' || c=='\f' || c=='\n'){
     return 1;
   }

   return 0;
}//method

int isDelimVar(char c){
   if(c=='\"' || c=='=' || c=='/' ||c=='*' ||c=='-' || c=='+' || c == ' ' || c=='\t'  || c == '\r' || c=='\v' || c=='\f' || c=='\n'){
     return 1;
   }

   return 0;
}//method

int isComment (char* command){
 int i=0;
 while (command[i] != NULL){
  if(isDelimiter(command[i])){
    i++;
    continue;
   }
   if(command[i] == '#'){
   return 1;
   }

  i++;
 }//while
 return 0;
}//method

int isHistory(char** command){
 int i=0;
 if(!strcmp(command[0],"history")){
   return 1;
 }//if
 return 0;
}//method

void assign_ (char* command,char** varTab){
 char key[512];
 char value[512];
 int k=0;
 int v=0;
 int i=0;
 int j=0;
 while (command[i] != NULL){
    if(isDelimiter(command[i]) == 1){
       i++;
       continue;
       }else{
        j=i;
        while(command[j] != NULL && !isDelimVar(command[j])){
         key[k] = command[j];
         k++;
         j++;
        }//while
        key[k] = NULL;

        while(command[j] != '='){
         j++;
        }
        j++;
        while (command[j] != NULL){
         if(isDelimiter(command[j]) == 1){
            goto INC;
          }else{
            while(command[j] != NULL && !isDelimiter(command[j])){
            value[v] = command[j];
            v++;
            j++;
            }//while
            value[v]= NULL;
            goto END;
          }//else
           INC:j++;
          }//While
       }//else
    i++;
 }//while
END:insertVar(key,value,varTab);
return ;

}//method


char ** getPaths(char* command, char*PATH){
   static char *output[600];
    int position = 0;

    int i=0;
    while(PATH[i] != NULL){

     if(PATH[i] == ':'){
       i++;
       continue;
     }else{
        int j=i;
        int k=0; //temp index
        char* temp = malloc(513 * sizeof(char));

        while(PATH[j] != NULL){
         if(PATH[j]==':'){
           i=j-1;
           temp[k] = '/';
           k++;
           j=0;
           while (command[j] != NULL){
            temp[k]=command[j];
            k++;
            j++;
           }//while
           temp[k] = NULL;
           output[position] = temp;
           position++; //---> different from Flow chart
           goto START;
         }else{
             temp[k]=PATH[j];
             k++;
         }//else
         j++;

        }//while
        START:;
     }//else
     i++;
    }//while
    output[position] = NULL; //---> different from Flow chart
    return output;
}//method

char* filterCommand (char* command,char** varTab){

   static char output2[513];
   int position = 0;
   int i=0;

   while (command[i] != NULL){
      if(isDelimiter(command[i]) == 1 || command[i] != '$'){
       output2[position] = command[i];
       position++;
       i++;
       continue;
       }else if(command[i] == '$'){
         int j=i+1;
         int k=0; //temp index
         char* key = malloc(513 * sizeof(char));

         while(command[j] != NULL && !isDelimVar(command[j])){
            key[k]=command[j];
            k++;
            j++;
         }//while
         key[j]=NULL;
         i=j-1;
         int indx = lookUp(key,varTab);
         char* value = varTab[indx];
         j=0;
         while(value[j] != NULL){
          output2[position]=value[j];
          j++;
          position++;
         }//while

       }//else if
       i++;
   }//while
    output2[position] = NULL; //---> different from Flow chart
    return output2;
}//method



char ** parse_commands(char* command)
{
    static char *output[600];
    int position = 0;
    int i=0;
    while(command[i] != NULL){

     if(isDelimiter(command[i]) == 1){
       i++;
       continue;
       }
     else if (command[i] == '\"'){
        int j=i+1;
        int k=0; //temp index
        char* temp = malloc(513 * sizeof(char));

        while(command[j] != '\"'){
          temp[k]=command[j];
          k++;
          j++;
        }//while
           i=j;
           temp[k] = NULL;
           output[position] = temp;
           position++; //---> different from Flow chart

     }else{
        int j=i;
        int k=0; //temp index
        char* temp = malloc(513 * sizeof(char));

        while(command[j] != NULL){
         if(isDelimiter(command[j])){
           i=j-1;
           temp[k] = NULL;
           output[position] = temp;
           position++; //---> different from Flow chart
           goto START;
         }else{
             temp[k]=command[j];
             k++;
         }//else
         j++;
        }//while
        START:;
     }//else
     i++;
    }//while
    output[position] = NULL; //---> different from Flow chart
    return output;
}//method





char * read_in(){
    static char buffer[600];
    fgets(buffer,600,stdin);
    if(strlen(buffer)>513){
     perror("Error: Command is bigger than 512 characters");
      return ;
    }

    return buffer;
}//method

char * read_File(FILE *fp){
    static char buffer[600];
    fgets(buffer, 600, (FILE*)fp);

    //fgets(buffer,600,stdin);
    if(strlen(buffer)>513){
     perror("Error: Command is bigger than 512 characters");
      return ;
    }

    if (!strcmp(buffer,"\n")){
     buffer[0] = 'e';
     buffer[1] = 'x';
     buffer[2] = 'i';
     buffer[3] = 't';
     buffer[4] = '\n';
    }//if

    return buffer;
}//method

char * read_Hist(FILE *fp){
    static char buffer[600];
    fgets(buffer, 600, (FILE*)fp);

    //fgets(buffer,600,stdin);
    if(strlen(buffer)>513){
     perror("Error: Command is bigger than 512 characters");
      return ;
    }

    return buffer;
}//method
