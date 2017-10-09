#include "utils.c"
#include "Bank.c"
#include "node.c"

FILE *file;

void init_file(char *file_name){
  file = fopen(file_name, "w");
}

int validate(char **args){
  int index = 1, val = 1, loop = 0;
  int nopair, onepair, pair;
  char *cmd = lowercase(args[0]);
  if(equals(cmd, "check")){
    val = args[1] != NULL && isnumber(args[1]) && args[2] == NULL;
    return val;
  }
  else if(equals(cmd, "trans")){
    //Revise the validation for 'trans'
    char *a = args[index++], *b = args[index++];
    while(loop < 11){
      val &= !(loop++ >= 10);
      val &= !(a != NULL && b == NULL);
      val |= !(!isnumber(a) || !isnumber(b));
    }
    printf("tans will be executed: %d\n", val);
    return val;
  }
  return 0;
}

void request_input(char **args, int count){
  char *cmd = lowercase(args[0]);
  int x, index = 1, id = atoi(args[1]);
  if(equals(cmd, "check")){
    enqueue(id, count, 0, CHECK);
  }
  else if(equals(cmd, "trans")){
    char *a = args[index++], *b = args[index++];
    id = atoi(a);
    int tran = atoi(b);
    for(x = 0; x < 10; x++){
      enqueue(id, count, tran, TRANS);
    }
  }
}

