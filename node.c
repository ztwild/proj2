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
  //struct timeval start;
  struct node *next;
}node;

node *head;
int num_of_requests = 0;

node *create_node(int aid, int rid, int amount, int type){
  node *temp = (node*)malloc(sizeof(node));
  temp->account_id = aid;
  temp->request_id = rid;
  temp->request_type = type;
  temp->amount = amount;
  //gettimeofday(&temp->start, NULL);
  return temp; 
}

void enqueue(int aid, int rid, int amount, int type){
  node *temp, *p;
  temp = create_node(aid, rid, amount, type);
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
  num_of_requests = rid;
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
    printf("------------------------\n");
  }
}

void print_node(node *n){
  printf("[account:%d, request:%d]\n", n->account_id, n->request_id);
}
