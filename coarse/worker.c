#include "utils.c"
#include "Bank.c"
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

int validate(char **args){
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


void process_next(){
  node *n;
  int ac, am, r;
  struct timeval end;
  
  if(get_request_type() == CHECK){
    n = dequeue();
    ac = n->account_id;
    r = n->request_id;
    am = n->amount;
    am = read_account(ac);
    gettimeofday(&end, NULL);
    fprintf(file, "%d BAL %d TIME %d.%06d %d.%06d\n", r, am,
      n->start.tv_sec, n->start.tv_usec, end.tv_sec, end.tv_usec);
    //fprintf(file, "%d BAL %d TIME %d.%06d\n", r, am,
      //end.tv_sec - n->start.tv_sec, end.tv_usec - n->start.tv_usec);
    free(n);
  }
  else{
    int *id_list = malloc(sizeof(int) * 10);
    int *tran_list = malloc(sizeof(int) * 10);
    int x = -1, loop = 1, valid = 1, index = 0;
    int size = bank_size;
    r = get_request_id();
    
    struct timeval start = head->start;
    while(loop){
      n = dequeue();
      valid &= n->account_id > 0 && n->account_id <= size;
      
      id_list[index] = n->account_id;
      if(valid){
        tran_list[index] = read_account(n->account_id) + n->amount;
        valid &= tran_list[index] >= 0;
      }
      
      x = valid || x > -1 ? x : index;
      loop = r == get_request_id();
      index++;
      free(n);
    }
    
    if(valid){
      for(x = 0; x < index; x++){
        write_account(id_list[x], tran_list[x]);
      }
      gettimeofday(&end, NULL);
      
      fprintf(file, "%d OK TIME %d.%06d %d.%06d\n", r,  
        start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
      //fprintf(file, "%d OK TIME %d.%06d\n", r,  
        //end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    }
    else{
      ac = id_list[x];
      gettimeofday(&end, NULL);
      fprintf(file, "%d ISF %d TIME %d.%06d %d.%06d\n", r, ac, 
        start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
      //fprintf(file, "%d ISF %d TIME %d.%06d\n", r, ac, 
        //end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
    }
    free(id_list);
    free(tran_list);
  }
  
}



