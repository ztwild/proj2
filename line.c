#include <stdio.h>
//#include <BaseTsd.h>
//typedef SSIZE_T ssize_t;

#define DEL " \n\t\r"
#define READ_SIZE 1024
#define SPLIT_SIZE 64
#define MAX_LEN 100

char *read_line(){
  int size = READ_SIZE, i = 0, c;
  char *arr = malloc(sizeof(char) * size);

  if (!arr) {
    printf("Read: Allocation Error\n");
    exit(1);
  }

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      arr[i] = '\0';
      return arr;
    } else {
      arr[i] = c;
    }
    i++;

    if (i >= size) {
      size += READ_SIZE;
      arr = realloc(arr, size);
      if (!arr) {
        printf("Read: Reallocation Error\n");
        exit(1);
      }
    }
  }
}

char **split_line(char *line){
  int size = SPLIT_SIZE, i = 0;
  char *tok, **arr = malloc(size * sizeof(char*));
  if(!arr){
    printf("Split: Allocation Error\n");
    exit(1);
  }

  tok = strtok(line, DEL);
  while (tok != NULL) {
    arr[i++] = tok;

    if (i >= size) {
      size += SPLIT_SIZE;
      arr = realloc(arr, size * sizeof(char*));
      if(!arr){
        printf("Split: Reallocation Error\n");
        exit(1);
      }
    }
    tok = strtok(NULL, DEL);
  }
  arr[i] = NULL;
  return arr;
}
