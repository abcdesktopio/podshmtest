#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <cstring>
#include "shmem.h"
using namespace std; 
  
int main() 
{ 
    int cmp_code = 0;	
    int exit_code = -1;
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("%s\n",str); 
    cmp_code = strcmp( str, MemContents );
      
    //detach from shared memory  
    exit_code = shmdt(str); 
    

    if (!exit_code) {
    	// destroy the shared memory 
    	exit_code = shmctl(shmid,IPC_RMID,NULL);
    } 

    if (!exit_code)
	exit_code = cmp_code; 
    
    return exit_code; 
} 
