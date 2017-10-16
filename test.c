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
  
  char *args1[] = {"check\0", "1\0", "\0"}; 
  //print_args(args1, "args1");
  char *args2[] = {"trans\0", "1\0", "20\0", "3\0", "-40\0", "\0"}; 
  //print_args(args2, "args2");
  char *args3[] = {"check\0", "3\0", "\0"};
  //print_args(args3, "args3");
  char *args4[] = {"trans\0", "1\0", "-20\0", "\0"};
  //print_args(args4, "args4");
  
  
  request_input(args1, c++);
  request_input(args2, c++);
  //request_input(args3, c++);
  //request_input(args4, c++);
  //printf("request inputs\n");
  
  print_list();

  return 0;
}
