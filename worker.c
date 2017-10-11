///**
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
//**/
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
    //Revise the validation for 'trans'
    int a, b, res;
    while(index < 11){
      a = isnumber(args[2(index - 1)]);
      b = isnumber(args[2(index)]);
      val = !(a || b) || (a && b);
      val &= val && index < 11;
      index++;
      
    }
    return val;
  }
  return 0
}

///**
void *worker(void *);

pthread_mutex_t mutex;
pthread_cond_t  worker_cv;
pthread_cond_t  bank_cv;
//**/

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

int process_check(int id){
  return read_account(id);
}

void process_trans(int id, int amount){
  
}


void *worker(void *arg){
  pthread_mutex_lock(&mutex);
  while(head == NULL)
    pthread_cond_wait( , &mutex); //for other workers
  ///get start time
  node *req = dequeue();
  if(req->request_type == CHECK){
    int amount = read_account(req->account_id);
    int id = req->request_id;
    
    fprintf(file, "%d BAL %d TIME %d.%d06d\n", id, amount, time);
  }
  
  
  free(req);
  //Record end time
  pthread_cond_brodcast(); //to workers
  pthread_mutex_unlock(&mutex);
  
  
}
