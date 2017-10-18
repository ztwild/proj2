#include "worker.c"

void print_args(char **args, char *name){
  int i = 0;
  while(args[i] != NULL){
    printf("%s[%d] = %s\n", name, i, args[i]);
    //printf("Equal to null: %d\n", args[])
    i++;
  }
  printf("-------Done--------\n");
}

int main(int argc, char **argv){
  int c = 0;
  
  char *args1[] = {"check", "1"};
  char *args2[] = {"trans", "2", "20", "3"};
  char *args3[] = {"check", "4"};
  char *args4[] = {"trans", "5", "-20"};
  
  request_input(args1, ++c);
  request_input(args2, ++c);
  request_input(args3, ++c);
  request_input(args4, ++c);
  
  //printf("request inputs\n");
  
  print_list2();

  return 0;
}
