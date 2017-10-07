#include <stdlib.h>
#include <stdio.h>

#define TRANS "trans"
#define CHECK "check"

typedef struct node{
  int account_id;
  int request_id;
  struct node *next;
}node;

node *head;

node *create_node(int aid, int rid){
  node *temp;
  temp = (node*)malloc(sizeof(node));
  temp->account_id = aid;
  temp->request_id = rid;
  temp->next = NULL;

  return temp; 
}

void enqueue(int aid, int rid){
  node *temp, *p;
  temp = create_node(aid, rid);
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
}

node *dequeue(){
  node *temp;
  temp = head;
  head = head->next;
  return temp;
}

void print_list(){
  node *temp;
  temp = head;
  if(head == NULL){
    printf("NULL\n");
  }
  else{
    while(temp->next != NULL){
      printf("[account:%d, request:%d]->", temp->account_id, temp->request_id);
      temp = temp->next;
    }
    printf("[account:%d, request:%d]\n", temp->account_id, temp->request_id);
  }
}