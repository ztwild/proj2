#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Bank.c"
#include "utils.c"
#include "node.c"

pthread_mutex_t mutex;
pthread_cond_t bank_cv;
pthread_cond_t account_cv;

int num_workers, num_accounts;
char *output_file;

void *bank_func();
void *worker_func();


int main(int argc, char **argv){
  char *line;
  
  initserver(argc, argv);
  
  ////// Declare Variables ///////
  num_workers = atoi(argv[1]);
  num_accounts = atoi(argv[2]);
  output_file = argv[3];
  int worker_index[num_workers];
  FILE *file = fopen(output_file, "w");
  
  pthread_t bank_tid;
  pthread_t worker_tid[num_workers];
  
  
  
  /////// Initialize Bank, mutex, and cond vars //////////
  initialize_accounts(num_accounts);
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&bank_cv, NULL);
  pthread_cond_init(&account_cv, NULL);
  
  //////// Create threads /////////
  pthread_create(&bank_tid, NULL, bank_func, NULL);
  int i;
  for(i = 0; i < num_workers; i++){
    worker_index[i] = i;
    pthread_create(&worker_tid[i], NULL, worker_func, NULL);
  }
  
  ////// Join Threads ///////
  pthread_join(bank_tid, NULL);
  for(i = 0; i < num_workers; i++){
    pthread_join(worker_tid[i], NULL);
  }
  
  printf("Threads are all created\n");
  
  //while(1){
    //read & parse input(fgets, tok)
    line = read_line();
    
    printf("out:%s\n", line);
    
    //CHECK
    
    //TRANS
    
    //END  
  //}
  
  fclose(file);
}


void *bank_func(){
  
}

void *worker_func(){
  
}
