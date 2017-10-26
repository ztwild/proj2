#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "line.c"
#include "worker.c"


pthread_mutex_t mutex;
pthread_cond_t  request_cv;
pthread_cond_t  process_cv;


void *request(void*);
void *process();

int inprocess, request_ready;

void run(int argc, char **argv){
  char *line, **args;
  int num_workers, num_accounts, request_count = 0;
  char *file_name;
  
  //// Declare Variables ////
  inprocess = 0;
  request_ready = 1;
  num_workers = atoi(argv[1]);
  num_accounts = atoi(argv[2]);
  file_name = argv[3];
  
  pthread_t request_tid;
  pthread_t process_tid[num_workers];
  
  //// Initialize Settings ////
  initialize_accounts(num_accounts);
  set_bank_size(num_accounts);
  init_file(file_name);
  create_account_list(num_accounts);
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&request_cv, NULL);
  pthread_cond_init(&process_cv, NULL);
  
  int i;
  for(i = 0; i < num_accounts; i++){
    pthread_create(&process_tid[i], NULL, (void*)&process, (void*)&i);
  }
  
  while(1){
    printf("> ");
    line = read_line();
    args = split_line(line);

    if(equals(args[0], "exit")){
      flockfile(file);
      int success = fprintf(file, "End of Simulation");
      fclose(file);
      exit(0);
    }
    else if(equals(args[0], "count")){
      printf("size %d\n", count_list());
      print_list();
    
    }
    else if(equals(args[0], "chk")){
      int i;
      printf("[ ");
      for(i = 0; i < bank_size-1; i++){
        printf("%d, ", account_list[i]->request);
      }
      printf("%d ]\n", account_list[i]->request);
      
    }
    else if(equals(args[0], "amt")){
      int i;
      printf("[ ");
      for(i = 0; i < bank_size-1; i++){
        printf("%d, ", account_list[i]->value);
      }
      printf("%d ]\n", account_list[i]->value);
      
    }
    else if(validate(args)){
      request_count++;
      int account, amount;
      char *cmd = lowercase(args[0]);
      worker *w = NULL;
      if(equals(cmd, "check")){
        account = atoi(args[1]);
        w = create_worker(CHECK, account, 0, request_count);
        pthread_create(&request_tid, NULL, (void*)&request, (void*)w);
      }
      else{
        int index = 1;
        while(args[index] != NULL){
          account = atoi(args[index++]);
          amount = atoi(args[index++]);
          worker *temp = create_worker(TRANS, account, amount, request_count);
          temp->next = w;
          w = temp;
        }
        pthread_create(&request_tid, NULL, (void*)&request, (void*)w);
      }
      printf("ID %d\n", request_count);
      //usleep(10000); // for testing, so it doesn't print the worker threads after 
    }
    else{
      printf("Invalid Input\n");
    }
    
    free(line);
    free(args);
  }
}


void *request(void *input){  //Main thread creates new thread to queue next request
  pthread_mutex_lock(&mutex);
  worker *w = (worker*)input;  
  
  while(inprocess > 0) //Waits till its number to queue
    pthread_cond_wait(&request_cv, &mutex);
  
  inprocess++;
  while(w != NULL){
    int type = w->type;
    int account = w->account;
    int amount = w->amount;
    int count = w->count;
    
    enqueue(type, account, amount, count);
    worker *temp = w;
    w = w->next;
    free(temp);
  }
  
  pthread_cond_broadcast(&request_cv);  //Gives priorety to the request
  pthread_cond_broadcast(&process_cv);  //Then the process
  
  inprocess--;
  pthread_mutex_unlock(&mutex);
  return ;
}


void *process(void* arg){  //Process/worker threads function
  
  //sleep(20);
//////////  Request queue  //////////
  int num = *((int*)arg);
  while(1){
    pthread_mutex_lock(&mutex);
    while(head == NULL || inprocess > 0)  //Waits till the head node in not null
      pthread_cond_wait(&process_cv, &mutex);
    inprocess++;
    
    int i, length = request_count();
    int *account_ids = malloc(sizeof(int)*length); //the ids of the accounts to process
    node *n = NULL;
    for(i = 0; i < length; i++){
      node *temp = dequeue();
      temp->next = n;
      n = temp;
      account_ids[i] = n->account_id;
    }
    
      //List of requests that need to be finished first
    int *priority = get_request_priority(account_ids, length);
    set_request_priority(account_ids, length, n->request_id);
    
    pthread_cond_broadcast(&request_cv);  //Gives priorety to the request
    pthread_cond_broadcast(&process_cv);  //Then the process
  
    inprocess--;
    pthread_mutex_unlock(&mutex);
 
    
//////////  Accounts  //////////
    
    lock_accounts(account_ids, length);
    i = isrequest_finished(priority);
    while(i >= 0){
      pthread_mutex_t mutex_account = account_list[i]->mutex;
      pthread_cond_wait(&account_cv, &mutex_account);
      i = isrequest_finished(priority);
    }
    
    char *str = process_next(n);
    free(priority);

    free_nodes(n);
    
    request_ready++;
    unlock_accounts(account_ids, length);
    free(account_ids);
    
//////////  Write to File  //////////    

    flockfile(file);
    fprintf(file, "%s", str);
    free(str);
    funlockfile(file);
    
  }
  
  return ;
}


