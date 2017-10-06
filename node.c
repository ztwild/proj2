#include <stdlib.h>
#include <stdio.h>

struct linkedlist{
  int data;
  struct linkedlist *next;
};

typedef struct linkedlist *node;

node createNode(int val){
  node temp;
  printf("temp is node\n");
  temp = (node)malloc(sizeof(struct linkedlist));
  temp->next = NULL;
  temp->value = val;
  printf("node temp isnt null\n");

  return temp; 
}

node addNode(node head, int value){
  node temp, p;
  temp = createNode(value);
  //temp->data = value;
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
  return head;
}
