#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
///**
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
//**/

#include "line.c"
#include "worker.c"

pthread_mutex_t mutex;
pthread_cond_t  request_cv;
pthread_cond_t  process_cv;

typedef struct temp{
  char **args;
  int count;
}temp;

temp *create_temp(char **args, int count){
  temp *t = (temp*)malloc(sizeof(temp));
  t->args = args;
  t->count = count;
  return t;
}

void *request(temp *t);
void *process();

void run(int argc, char **argv){
  char *line, **args;
  int num_workers, num_accounts, request_count = 0;
  char *file_name;

  //// Declare Variables ////
  num_workers = atoi(argv[1]);
  num_accounts = atoi(argv[2]);
  file_name = argv[3];
  pthread_t process_tid[num_workers];
  
  //// Initialize Settings ////
  initialize_accounts(num_accounts);
  init_file(file_name);
  
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&request_cv, NULL);
  pthread_cond_init(&process_cv, NULL);
  
  /**
  int i;
  for(i = 0; i < num_accounts; i++){
    pthread_create(&process_tid[i], NULL, process, NULL);
  }
  **/
	
  
  while(1){
    printf("> ");
    line = read_line();
    args = split_line(line);

    if(equals(args[0], "exit")){
      int success = fprintf(file, "End of Simulation");
      fclose(file);
      exit(0);
    }
    else if(equals(args[0], "count")){
      printf("size %d, ", count_list());
      print_list();
    
    }
    else if(validate(args)){
      request_count++;
      temp *t = create_temp(args, request_count);
      pthread_t request_tid;
      pthread_create(&request_tid, NULL, request(t), NULL);
      printf("ID %d\n", request_count);
    }
    else{
      printf("Invalid Input\n");
    }
     
    free(line);
    free(args);
  }
}


void *request(temp *t){
  pthread_mutex_lock(&mutex);
  while(0) //Waits till its number to queue
    pthread_cond_wait(&request_cv, &mutex);
  
  //request_input(t->args, t->count);
  pthread_cond_broadcast(&request_cv);  //Gives priorety to the request
  pthread_cond_broadcast(&process_cv);  //Then the process
  pthread_mutex_unlock(&mutex);

  printf("request submitted\n");
}


void *process(){
  pthread_mutex_lock(&mutex);
  while(head == NULL)  //Waits till the head node in not null
    pthread_cond_wait(&process_cv, &mutex);
    
  process_next();
  pthread_cond_broadcast(&request_cv);  //Gives priorety to the request
  pthread_cond_broadcast(&process_cv);  //Then the process
  pthread_mutex_unlock(&mutex);
  
  //printf("process finished\n");
}

