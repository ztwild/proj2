#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int isnumber(char *str){
  int i, b = 1;
  i = (str[0] == '+' || str[0] == '-') && strlen(str) > 1 ; //if first char is '+' OR '-', ignore
  
  for(i; i < strlen(str); i++){
    b &= isdigit(str[i]) > 0;
  }
  return b;
}

int equals(char *str1, char *str2){
  return strcmp(str1, str2) == 0;
}

char *lowercase(char *str){
  int i = 0;
  while(str[i] != '\0'){
    str[i] = tolower(str[i]);
    i++;
  }
  return str;
}
