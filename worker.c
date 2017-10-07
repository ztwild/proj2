#include "utils.c"
#include "Bank.c"
#include "node.c"

FILE *file;

void init_file(char *file_name){
  file = fopen(file_name, "w");
}

int validate(char **args){
  int index = 1, val = 1;
  char *cmd = lowercase(args[0]);
  if(equals(cmd, "check")){
    val = args[1] != NULL && isnumber(args[1]) && args[2] == NULL;
    return val;
  }
  else(equals(cmd, "trans")){
    return 0;
  }
  return 0;
}

void request_input(char **args, int count){
  char *cmd = lowercase(args[0]);
  int index = 1, id = atoi(args[1]);
  if(equals(cmd, "check")){
    enqueue(id, count, 0, CHECK);
  }
  else if(equals(cmd, "trans")){
    index = 2;
  }
  
}



