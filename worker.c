#include "utils.c"
#include "Bank.c"
#include "node.c"

FILE *file;

void init_file(char *file_name){
  file = fopen(file_name, "w");
}

int validate(char **args){
  int index = 1, val = 1, loop = 1;
  int nopair, onepair, pair;
  char *cmd = lowercase(args[0]);
  if(equals(cmd, "check")){
    val = args[1] != NULL && isnumber(args[1]) && args[2] == NULL;
    return val;
  }
  else if(equals(cmd, "trans")){
    char *a, *b;
    while(1){
      a = args[2 * index - 1];
      b = args[2 * index];
      
      if(a == NULL && b == NULL){
        return index > 1;
      }
      else if(isnumber(a) ^ isnumber(b) && a != NULL && b != NULL){
        return 0;
      }
      else if(index > 10){
        return 0;
      }
      index++;
    }
    
    return 1;
  }
  return 0;
}

void request_input(char **args, int count){
  char *cmd = args[0];
  int id; 
  if(equals(cmd, "check")){
    id = atoi(args[1]);
    enqueue(id, count, 0, CHECK);
  }
  else if(equals(cmd, "trans")){
    printf("in trans\n");
    int i, tran;
    for(i = 1; i < 11; i++){
      id = atoi( args[2 * i - 1] );
      tran = atoi( args[2 * i] );
      enqueue(id, count, tran, TRANS);
      i = (args[2 * i + 1] != NULL) ? i : 11;
    }
  }
}

void process_next(){
  //flockfile(file);
  node *n = dequeue();
  
  if(n->request_type == CHECK){
    int amount = read_account(n->account_id);
    fprintf(file, "%d BAL %d TIME ---\n", n->request_id, amount);
  }
  else{
    write_account(n->account_id, n->amount);
    //printf("run.c: about to write to file\n");
    int success = fprintf(file, "%d BAL %d TIME ---\n", n->request_id, n->amount);
    printf("wrote to file: %d\n", success);
  }
  free(n);
  //funlockfile(file);
}




