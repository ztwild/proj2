#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct account{
  pthread_mutex_t mutex;
  int value;
  int request;
}account;

account **account_list;
pthread_cond_t account_cv;
int size;

int *request_priority;

account *create_account(){
  account *a = malloc(sizeof(account));
  pthread_mutex_init(&a->mutex, NULL);
  a->value = 0;
  a->request = 0;
  return a;
}

void create_account_list(int n){
  size = n;
  account_list = malloc(sizeof(account*)*size);
  request_priority = malloc(sizeof(int) * size);
  pthread_cond_init(&account_cv, NULL);
  int i;
  for(i = 0; i < n; i++){
    account_list[i] = create_account();
    request_priority[i] = 0;
  }
  
}

int *get_request_priority(){
  int i, *list = malloc(sizeof(int)*size);
  for(i = 0; i < size; i++){
    list[i] = request_priority[i];
  }
  return list;
}


void set_request_priority(int *list, int n, int count){
  int i, id;
  for(i = 0; i < n; i++){
    id = list[i];
    request_priority[id] = count;
  }
}

int isrequest_finished(int *list, int n, int count){
  int i;
  for(i = 0; i < n; i++){
    int r = account_list[i]->request;
    
  }
  return 0;
}

void set_finished_priority(int *list){
  
}

/// Locking and Unlocking
void lock_accounts(int *list, int size){
  int i;
  pthread_cond_broadcast(&account_cv);
  for(i = 0; i < size; i++){
    pthread_mutex_lock(&account_list[i]->mutex);
  }
}

void unlock_accounts(int *list, int size){
  int i;
  for(i = 0; i < size; i++){
    pthread_mutex_unlock(&account_list[i]->mutex);
  }
}

void account_waiting(int *list, int size){
  int i;
  for(i = 0; i < size; i++){
    pthread_cond_wait(&account_cv, &account_list[i]->mutex);
  }
}
