#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct account{
  pthread_mutex_t mutex;
  int value;
}account;

account **account_list;
pthread_cond_t account_cv;

account *create_account(){
  account *a = malloc(sizeof(account));
  pthread_mutex_init(&a->mutex, NULL);
  a->value = 0;
  return a;
}

void create_account_list(int n){
  account_list = malloc(sizeof(account*)*n);
  pthread_cond_init(&account_cv, NULL);
  int i;
  for(i = 0; i < n; i++){
    account_list[i] = create_account();
  }
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
