#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define TRANS 0
#define CHECK 1

typedef struct node{
  int account_id;
  int request_id;
  int request_type;
  int amount;
  struct timeval start;
  struct node *next;
}node;

node *head = NULL;
int num_of_requests = 0;

node *create_node(int type, int aid, int amount, int rid){
  node *temp = (node*)malloc(sizeof(node));
  temp->account_id = aid;
  temp->request_id = rid;
  temp->request_type = type;
  temp->amount = amount;
  gettimeofday(&temp->start, NULL);
  return temp; 
}

void enqueue(int type, int account, int amount, int count){
  node *temp, *p;
  temp = create_node(type, account, amount, count);
  temp->next = NULL;
  if(head == NULL){
    head = temp;
  }
  else{
    p = head;
    while(p->next != NULL){
      p = p->next;
    }
    p->next = temp;
  }
  //num_of_requests = rid;
}

node *dequeue(){
  node *temp;
  temp = head;
  head = head->next;
  return temp;
}

int count_list(){
  node *temp = head;
  int count = 0;
  while(temp != NULL){
    count ++;
    temp = temp->next;
  }
  return count;
}

int get_request_id(){
  return head == NULL ? 0 : head->request_id;
}

int get_request_type(){
  return head == NULL ? 0 : head->request_type;
}

int request_count(){
  node *n = head;
  int j = 0, i = n->request_id;
  while(n != NULL && n->request_id == i){
    j++;
    n = n->next;
  }
  return j;
}

void print_list(){
  node *temp;
  temp = head;
  if(head == NULL){
    printf("NULL\n");
  }
  else{
    int a = temp->account_id;
    int r = temp->request_id;
    while(temp->next != NULL){
      printf("[account:%d, request:%d]\n", a, r);
      temp = temp->next;
      a = temp->account_id;
      r = temp->request_id;
    }
    printf("[account:%d, request:%d]\n", a, r);
  }
}

void print_node(node *n){
  printf("[account:%d, request:%d]\n", n->account_id, n->request_id);
}

void print_list2(){
  node *temp;
  temp = head;
  if(head == NULL){
    printf("NULL\n");
  }
  else{
    int a = temp->account_id;
    int r = temp->amount;
    while(temp->next != NULL){
      printf("[account:%d, amount:%d]\n", a, r);
      temp = temp->next;
      a = temp->account_id;
      r = temp->amount;
    }
    printf("[account:%d, amount:%d]\n", a, r);
    printf("------------------------\n");
  }
}

void free_nodes(node *n){
  while(n != NULL){
    node *temp = n->next;
    free(n);
    n = temp;
  }
}

