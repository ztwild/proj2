#include "run.c"


int main(int argc, char **argv){

  initserver(argc, argv);
  
  run(argc, argv);

  return 0;
}
