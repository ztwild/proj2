#include "utils.c"
#include "Bank.c"
#include "account.c"
#include "node.c"

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
       // printf("end of list\n");
        return index > 1;
      }
      else if((a != NULL || b != NULL) && isnumber(a) ^ isnumber(b)){
        //printf("a = %s, b = %s\n", a, b);
       // printf("uneven amount of numbers\n");
        return 0;
      }
      else if(index > 10){
        //printf("input out of bounds\n");
        return 0;
      }
      //else{
       // printf("a = %s, b = %s\n", a, b);
        //printf("OK\n");
      //}
      index++;
    }
    
    return 1;
  }
  return 0;
}


char *process_next(node *n){  ///Dequeues the next list of nodes with same request id 
  char *str = malloc(sizeof(char)* 100);
  int ac, am, r;
  struct timeval end, start = n->start;
  
  if(n->request_type == CHECK){
    ac = n->account_id;
    r = n->request_id;
    am = n->amount;
    //am = read_account(ac);
    am = account_list[ac - 1]->value;
    gettimeofday(&end, NULL);
    sprintf(str, "%d BAL %d TIME %d.%06d %d.%06d\n", r, am,
      start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
    // sprintf(str, "%d BAL %d TIME %d.%06d\n", r, am,
    //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    free(n);
  }
  else{
    int *id_list = malloc(sizeof(int) * 10);
    int *tran_list = malloc(sizeof(int) * 10);
    int x = -1, loop = 1, valid = 1, index = 0;
    int size = bank_size;
    r = n->request_type;
    
    while(n != NULL){
      valid &= n->account_id > 0 && n->account_id <= size;
      
      id_list[index] = n->account_id;
      if(n->account_id > 0 && n->account_id <= size){
        tran_list[index] = account_list[n->account_id - 1]->value + n->amount;
        account_list[n->account_id - 1]->request = n->request_id;
        //tran_list[index] = read_account(n->account_id) + n->amount;
        valid &= tran_list[index] >= 0;
      }
      
      x = valid || x > -1 ? x : index;
      loop = n->next != NULL;
      index++;
      node *temp = n;
      n = n->next;
      free(temp);
    }
    
    if(valid){
      for(x = 0; x < index; x++){
        write_account(id_list[x], tran_list[x]);
      }
      gettimeofday(&end, NULL);
      //fprintf(file, "(%d) ", index); 
      sprintf(str, "%d OK TIME %d.%06d %d.%06d\n", r, 
      //fprintf(file, "%d OK TIME %d.%06d %d.%06d\n", r, 
        start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
      // sprintf(str, "%d OK TIME %d.%06d\n", r, 
      //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    }
    else{
      ac = id_list[x];
      gettimeofday(&end, NULL);
      sprintf(str, "%d ISF %d TIME %d.%06d %d.%06d\n", r, ac, 
        start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
      // sprintf(str, "%d ISF %d TIME %d.%06d\n", r, ac, 
      //   end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    }
    free(id_list);
    free(tran_list);
  }
  return str;
}



