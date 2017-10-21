#include "run.c"

int initserver(int argc, char **argv){
  //printf("checking for server init..\n");
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



int main(int argc, char **argv){
  initserver(argc, argv);
  
  run(argc, argv);

  return 0;
}
