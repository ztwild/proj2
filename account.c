#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

///// Testing /////
void print_account_requests(int size);
void print_account_ids(int *list, int n);
///// Testing /////

typedef struct account{
  pthread_mutex_t mutex;
  int value;
  int request;
}account;

int size, *request_priority;
account **account_list;
pthread_cond_t account_cv;


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

int *get_request_priority(int *accounts, int n){
  int i, *list = malloc(sizeof(int)*size);
  
  for(i = 0; i < size; i++){
    list[i] = 0;
  }
  for(i = 0; i < n; i++){
    int id = accounts[i];
    list[id - 1] = request_priority[id - 1];
  }
  return list;
}


void set_request_priority(int *list, int n, int count){
  int i, id;
  for(i = 0; i < n; i++){
    id = list[i];
    request_priority[id-1] = count;
  }
}


int isrequest_finished(int *priority){
  /**
  printf("Priority list->");
  print_account_ids(priority, size);
  printf("Accounts processed->");
  print_account_requests(size);
  **/
  int i;
  for(i = 0; i < size; i++){
    int r = account_list[i]->request;
    if(priority[i] > 0 && priority[i] != r){
      return i;
    }
  }
  return -1;
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

//////// Testing ////////
void print_account_requests(int size){
  int i;
  printf("[ ");
  for(i = 0; i < size - 1; i++){
    printf("%d, ", account_list[i]->request);
  }
  printf("%d ]\n", account_list[i]->request);
}

void print_account_ids(int *list, int n){
  int i;
  printf("[ ");
  for(i = 0; i < n-1; i++){
    printf("%d, ", list[i]);
  }
  printf("%d ]\n", list[i]);

}



