#include <signal.h>
#include <stdio.h>
//#include <windows.h>

#define MSGSIZE 16

/////// 3.1 ///////
/**
void my_routine( );
int main( ) {
  signal(SIGINT, my_routine);
  printf("Entering infinite loop\n");
  while(1) {
    sleep(10);
  } // take an infinite number of naps
  printf("Can’t get here\n");
}
  // will be called asynchronously, even during a sleep

void my_routine( ) {
  printf("Running my_routine\n");
}
**/

/////// 3.2 ///////
/**
void my_routine( );
int main() {
  signal(SIGINT, my_routine);
  signal(SIGQUIT, my_routine);
  printf("Entering infinite loop\n");
  while(1) { 
    sleep(10); 
  }
  printf("Can’t get here\n");
}

void my_routine(int signo) {
  printf("The signal number is %d.\n", signo);
}
**/

/////// 3.4 ///////
/**
char msg[100];
void my_alarm();
int main(int argc, char * argv[]){
  int time;
  if (argc < 3) {
    printf("not enough parameters\n");
    exit(1);
  }
  time = atoi(argv[2]);
  strcpy(msg, argv[1]);
  signal(SIGALRM, my_alarm);
  alarm(time);
  printf("Entering infinite loop\n");
  while (1) { 
      sleep(10);
  }
  printf("Can’t get here\n");
}

void my_alarm() {
  printf("%s\n", msg);
  exit(0);
}
**/

/////// 3.5 ///////
/**
int main() {
  char *msg = "How are you?";
  char inbuff[MSGSIZE];
  int p[2];
  int ret;
  pipe(p);
  ret = fork( );
  if (ret > 0) {
    write(p[1], msg, MSGSIZE);
  } 
  else {
    sleep(1);
    read(p[0], inbuff, MSGSIZE);
    printf("%s\n", inbuff);
  }
  exit(0);
}
**/

/////// 3.6 ///////
void my_routine( );
int ret;
int main() {
  ret = fork( );
  signal(SIGINT, my_routine);
  printf("Entering infinite loop\n");
  while(1) { 
    sleep(10); 
  }
  printf("Can’t get here\n");
}
void my_routine() {
  printf("Return value from fork = %d\n", ret);
}
