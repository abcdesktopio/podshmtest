#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <cstring>
#include "shmem.h"
using namespace std; 
int main() 
{ 
    int exit_code = -1;
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    strcpy( str, MemContents );
      
    //detach from shared memory  
    exit_code = shmdt(str); 
  
    return exit_code; 
}
