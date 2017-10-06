#include <stdlib.h>
#include <stdio.h>

struct linkedlist{
  int account_id;
  int request_id;
  //type
  struct linkedlist *next;
};

typedef struct linkedlist *node;

node create_node(int aid, int rid){
  node temp;
  temp = (node)malloc(sizeof(node));
  if(temp = NULL){
    printf("Cannot Create Node\n");
    exit(0);
  }
  temp->account_id = aid;
  temp->request_id = rid;
  temp->next = NULL;
  return temp;
  
}

void print_list(node head){
  if(head != NULL){
    printf("");
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

