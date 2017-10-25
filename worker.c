#include <time.h>
#include <sys/time.h>
#include "utils.c"
#include "Bank.c"
#include "account.c"
#include "node.c"
#include "test.c"

///  File  ///
FILE *file;

void init_file(char *file_name){
  file = fopen(file_name, "w+");
}

///  Worker  ///
typedef struct worker{
  int type;
  int account;
  int amount;
  int count;
  struct worker *next;
}worker;

worker *create_worker(int type, int account, int amount, int count){
  worker *temp = (worker*)malloc(sizeof(worker));
  temp->type = type;
  temp->account = account;
  temp->amount = amount;
  temp->count = count;
  temp->next = NULL;
  return temp;
}


///  Buisness Logic  ///
int bank_size;
void set_bank_size(int size){
  bank_size = size;
}

int validate(char **args){ ///Validates if the user input is valid
  int index = 1, val = 1;
  char *cmd = lowercase(args[0]);
  if(equals(cmd, "check")){
    val = args[1] != NULL && isnumber(args[1]) && args[2] == NULL;
    return val;
  }
  else if(equals(cmd, "trans") && args[1] != NULL){
    char *a, *b;
    while(1){
      a = args[2 * index - 1];
      b = args[2 * index];
      
      if(a == NULL){
        return index > 1;
      }
      else if((a != NULL || b != NULL) && isnumber(a) ^ isnumber(b)){
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

char *process_check(node *);
char *process_trans(node *);

char *process_next(node *n){  ///Dequeues the next list of nodes with same request id 
  if(n->request_type == CHECK){
    return process_check(n);
  }
  else{
    return process_trans(n);
  }
}

////////  Process Check  ////////
char *process_check(node *n){
  char *str = malloc(sizeof(char)* 100);
  int index = n->account_id - 1;
  int amount = account_list[index]->value;
  account_list[index]->request = n->request_id;
  
  struct timeval end, start = n->start;
  gettimeofday(&end, NULL);
  sprintf(str, "%d BAL %d TIME %d.%06d %d.%06d\n", n->request_id, amount,
    start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
  // sprintf(str, "%d BAL %d TIME %d.%06d\n", r, am,
  //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
  
  free(n);
  return str;
}

////////  Process Trans  ////////
char *process_trans(node *n){
  char *str = malloc(sizeof(char)* 100);
  struct timeval end, start = n->start;
  int *id_list = malloc(sizeof(int) * 10);
  int *tran_list = malloc(sizeof(int) * 10);
  int x = -1, loop = 1, valid = 1, index = 0;
  int r = n->request_id;
  print_nodes(n);
  
  
  while(n != NULL){
    valid &= n->account_id > 0 && n->account_id <= bank_size;
    id_list[index] = n->account_id;
    
    if(n->account_id > 0 && n->account_id <= bank_size){
      tran_list[index] = account_list[n->account_id - 1]->value + n->amount;
      account_list[n->account_id - 1]->request = r;
      //tran_list[index] = read_account(n->account_id) + n->amount;
      valid &= tran_list[index] >= 0;
    }
    x = valid || x > -1 ? x : index;
    loop = n->next != NULL;
    index++;
    node *temp = n->next;
    n = n->next;
    free(temp);
  }
  
  if(valid){
    for(x = 0; x < index; x++){
      write_account(id_list[x], tran_list[x]);
    }
    gettimeofday(&end, NULL);
    sprintf(str, "%d OK TIME %d.%06d %d.%06d\n", r, 
    //fprintf(file, "%d OK TIME %d.%06d %d.%06d\n", r, 
      start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
    // sprintf(str, "%d OK TIME %d.%06d\n", r, 
    //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
  }
  else{
    int account = id_list[x];
    gettimeofday(&end, NULL);
    sprintf(str, "%d ISF %d TIME %d.%06d %d.%06d\n", r, account, 
      start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
    // sprintf(str, "%d ISF %d TIME %d.%06d\n", r, ac, 
    //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
  }
  free(id_list);
  free(tran_list);
  return str;
}




