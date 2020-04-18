#include "types.h"
#include "user.h"

int main(int argc, char *choice[])
{
  int test1(void);
  int test2(void);
	
  if (atoi(choice[1]) == 1)
	test1();
  else if (atoi(choice[1]) == 2)
	test2();
  else{ 
      printf(1, " Run waittest 1 for testing exit() and wait()\n");
      printf(1, " Run waittest 2 for testing waitpid()\n");  
  }
  // End of test
  exit(0);
 }
  
  
int test1(void) {
  int pid, pid2, exitStatus;
  
  printf(1, "\nTESTING CASE : EXIT() AND WAIT()\n");

  for (int i = 0; i < 2; i++) {
    pid = fork();
    // Chlid access 
    if (pid == 0) 
    {  
      if (i == 0)
      {
      	printf(1, "CHILD: %d , EXIT Status:  %d\n", getpid(), 0);
      	exit(0);
      }
      else
      {
        printf(1, "CHILD: %d , EXIT Status:  %d\n", getpid(), 0);	
      	exit(-1);
      } 
    }
    // Parent access
    else if (pid > 0) { 
      // Testing wait function
      pid2 = wait(&exitStatus);
      printf(1, "PARENT OF CHILD: %d, CHILD EXITED WITH STATUS:  %d\n", pid2, exitStatus);
    }
    // Segmentation fault : fork()
    else  
    {  
      printf(2, "Segmentation fault : fork()\n");
      exit(-1);
    }
  }
  printf(1,"\n");
  return 0;
}

int test2(void){
	
  int pid2, exitStatus, pidHold;
  int child[3]={0,0,0};
  
  printf(1, "\nTESTING CASE : WAITPID()\n");

  for (int i = 0; i < 3; i++) {
    child[i] = fork();
    // CHILD ACCESS
    if (child[i] == 0) {       
     pidHold = getpid(); 
     printf(1, "CHILD:  %d ,EXIT STATUS: %d\n", pidHold, 0);
     exit(0);
    }
   }
       
  for(int j = 0 ; j < 3 ; j++){
      sleep(5);
      printf(1, "Parent Node: Waiting...Child: %d\n",child[j]);
      pid2 = waitpid(child[j], &exitStatus, 0);
      printf(1, "Waitpid() successful executed!\n");
      printf(1, "This is the parent: Child# %d has exited with status %d\n",pid2, exitStatus);
  } 
  
  printf(1,"\n");    
  return 0;
}
     
