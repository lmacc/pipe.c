#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


//Leslie McCarthy DNET 3
int main(){

 pid_t pid = getpid();
 pid_t childpid, childpid2;
 
 int pip1Fds[2];
 pipe(pip1Fds);
 
 
 printf("STARTING PROCESS PID %d\n",pid);

 // Add the code for the two children here
  
    childpid = fork();
   
 
    if (childpid < 0){
        perror("fork failed");
        exit(-1);
    }
    
    else if (childpid == 0){
       
        char message[256];
        char messageRead[256];
        sprintf(message, "hello from process id %d", (int) getpid());
        int written = write(pip1Fds[1], message,strlen(message) + 1);        
        printf("CHILD1: The number of bytes written is %d\n", written);       
         
         
        int numBytesRead = read(pip1Fds[0], messageRead,sizeof(messageRead));           
        printf("CHILD1: The length of message received from CHILD2 is: %d\n", numBytesRead);
        printf("CHILD1: MESSAGE CONTENT FROM CHILD2 is: %s\n",messageRead);
        
             
        close(pip1Fds[0]);       
        close(pip1Fds[1]);  
        
        
        exit(0);
    }
   
    
    
    else {//Parent process     
        
         childpid2 = fork();
        
         if (childpid2 < 0){
            perror("fork failed for child 2");
            exit(-1);
        }
        
        else if (childpid2 == 0){
           
        char messageRead[256];
        char message[256];     
            
        sprintf(message, "hello from process id %d\n", (int) getpid());
        int written = write(pip1Fds[1], message,strlen(message) + 1);
        printf("CHILD2: The number of bytes written is %d\n", written);
        
            
        int numBytesRead = read(pip1Fds[0], messageRead,sizeof(messageRead));           
        printf("CHILD2: The length of message received from CHILD1 is: %d\n", numBytesRead);
        printf("CHILD2: MESSAGE CONTENT FROM CHILD1 is: %s\n",messageRead);
            
        close(pip1Fds[0]);
        close(pip1Fds[1]);
            
        exit(0);
        }        
     
       
       
         
    }
    
    close(pip1Fds[0]);
    close(pip1Fds[1]);
    for(int i = 0; i < 2; i++)
        wait(NULL);
           
    printf("\nPARENT: PROCESS Waiting on children to complete\n");
       sleep(3);      
    
    printf("\nFinal Print Statement before exit\n");
       
        
 exit(0);
 
}