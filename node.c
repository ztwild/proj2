#include <stdlib.h>
#include <stdio.h>

typedef struct linkedlist{
  int account_id;
  int request_id;
  //type
  struct linkedlist *next;
}*node;

//typedef struct linkedlist *node;

node create_node(int aid, int rid){
  node temp;
  temp = (node)malloc(sizeof(struct linkedlist));
  if(temp = NULL){
    exit(0);
  }
  // printf("account id is %d\n", temp.account_id);
  printf("setting node params\n");
  temp->account_id = aid;
  printf("setting account it\n");
  temp->request_id = rid;
  temp->next = NULL;
  return temp; 
}

void print_list(node head){
  if(head != NULL){
    printf("[account:%d, request:%d]->", head->account_id, head->request_id);
    print_list(head->next);
  }
  else{
    printf("\n");
  }
}


void enqueue(node head, node insert){
  node temp, current;
  if(head == NULL){
    head = insert;
  }
  else{
    current = head;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = insert;
  }
}


node dequeue(node head){
  node car;
  car = head;
  head = head->next;
  return head;
}

