#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int isnumber(char *str){
  if(str == NULL){
    return 0;
  }
  int i, b = 1;
  //if first char is '+' OR '-', ignore
  i = (str[0] == '+' || str[0] == '-') && strlen(str) > 1 ; 
  
  for(i; i < strlen(str); i++){
    b &= isdigit(str[i]) > 0;
  }
  return b;
}

int equals(char *str1, char *str2){
  if(str1 == NULL || str2 == NULL){
    return !(str1 == NULL ^ str2 == NULL);
  }
  return strcmp(str1, str2) == 0;
}

char *lowercase(char *str){
  if(str == NULL){
    return NULL;
  }
  int i = 0;
  while(str[i] != '\0'){
    str[i] = tolower(str[i]);
    i++;
  }
  return str;
}


