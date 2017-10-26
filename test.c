#include <signal.h>
#include <stdio.h>
#include <windows.h>

/////// 3.1 ///////
/**
void my_routine( );
int main( ) {
  signal(SIGINT, my_routine);
  printf("Entering infinite loop\n");
  while(1) {
    Sleep(10);
  } // take an infinite number of naps
  printf("Can’t get here\n");
}
  // will be called asynchronously, even during a sleep

void my_routine( ) {
  printf("Running my_routine\n");
}
**/

/////// 3.2 ///////
void my_routine( );
int main() {
  signal(SIGINT, my_routine);
  signal(sigQUIT, my_routine);
  printf("Entering infinite loop\n");
  while(1) { 
    Sleep(10); 
  }
  printf("Can’t get here\n");
}

void my_routine(int signo) {
  printf("The signal number is %d.\n", signo);
}
