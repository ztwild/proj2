#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.c"
#include "line.c"

int initserver(int argc, char **argv){
  printf("checking for server init..\n");
  if(argc != 4){
    printf("Number of arguments invalid, exiting\n");
    exit(0);
  }
  else if(!isnumber(argv[1]) || !isnumber(argv[2])){
    printf("Second or third arguments are not numeric, exiting\n");
    exit(0);
  };
  printf("server initialized\n");
  return 1;
}

void run(int argc, char **argv){
  char *line, **args;
  int num_workers, num_accounts, *worker_index;
  char *file_name, *cmd;

  ////// Declare Variables ///////
  num_workers = atoi(argv[1]);
  num_accounts = atoi(argv[2]);
  file_name = argv[3];
  worker_index = (int*)malloc(sizeof(int) * num_workers);
  FILE *file = fopen(file_name, "w");

  while(1){
    printf("> ");
    line = read_line();
    printf("getting line..: %s\n", line);
    args = split_line(line);
    cmd = lowercase(args[0]);
    printf("input: %s\n", cmd);
    if(equals(cmd, "exit")){
      fclose(file);
      printf("Exiting");
      exit(0);
    }
    else if(equals(cmd, "tran")){
      printf("Transaction\n");
    }
    else if(equals(cmd, "check")){
      printf("Bill Check\n");
    }
    

    free(line);
    free(args);
  }

}