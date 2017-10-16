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
  char *args[10];

  char *args1[] = {"check", "1", NULL, NULL, NULL};
  request_input(args1, ++c);
  print_list();
  printf("------\n");

  char *args2[] = {"trans", "1", "30", NULL, NULL};
  request_input(args2, ++c);
  print_list();
  printf("------\n");

  return 0;
}
