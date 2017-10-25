void print_account_ids(int *list, int n){
  int i;
  printf("[ ");
  for(i = 0; i < n-1; i++){
    printf("%d, ", list[i]);
  }
  printf("%d ]\n", list[i]);

}

void print_account_requests(int size){
  int i;
  printf("[ ");
  for(i = 0; i < size - 1; i++){
    printf("%d, ", account_list[i]->request);
  }
  printf("%d ]\n", account_list[i]->request);
}

void print_nodes(node *n){
  node *temp = n;
  printf("( ");
  while(temp->next != NULL){
    printf("%d, ", temp->request_id);
    temp = temp->next;
  }
  printf("%d )\n", temp->request_id);
}


