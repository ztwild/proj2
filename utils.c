#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 100
#define DEL " \n\t\r"

int isnumber(char *str){
  int i, b = 1;
  i = (str[0] == '+' || str[0] == '-') && strlen(str) > 1 ; //if first char is '+' OR '-', ignore
  
  for(i; i < strlen(str); i++){
    printf("index %d: isdigit %d\n", i, isdigit(str[i]) > 0);
    b &= isdigit(str[i]) > 0;
  }
  return b;
}

int initserver(int argc, char **argv){
  printf("checking for server init..\n");
  if(argc != 4){
    printf("Number of arguments invalid, exiting\n");
    exit(0);
  }
  else if(!isnumber(argv[1]) || !isnumber(argv[2])){
    printf("Second or third arguments are not numeric, exiting\n");
    exit(0);
  };
  printf("server initialized\n");
  return 1;
}

char *read_line(){
  char line[MAX_LEN], *str;
  fgets(line, MAX_LEN, stdin);
  str = strtok(line, DEL);
  return str;
}
