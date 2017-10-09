#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "line.c"
#include "worker.c"

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
  
  return 1;
}

void run(int argc, char **argv){
  char *line, **args;
  int num_workers, num_accounts, *worker_index, count = 0;
  char *file_name;

  //// Declare Variables ////
  num_workers = atoi(argv[1]);
  num_accounts = atoi(argv[2]);
  file_name = argv[3];
  worker_index = (int*)malloc(sizeof(int) * num_workers);

  initialize_accounts(num_accounts);
  init_file(file_name);

  while(1){
    count++;
    printf("> ");
    line = read_line();
    args = split_line(line);
    
    if(equals(args[0], "exit")){
      fclose(file);
      printf("Exiting");
      exit(0);
    }
    // else if(){
    //   printf("Transaction\n");
    // }
    else if(validate(args)){
      request_input(args, count);
      printf("ID %d\n", count);
    }
    else{
      printf("Not Valid Input\n");
    }
    

    free(line);
    free(args);
  }

}