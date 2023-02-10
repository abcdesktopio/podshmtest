#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <cstring>
#include "shmem.h"
using namespace std; 
  
int main() 
{ 
    printf("receive starts\n");
    int cmp_code = 0;	
    int exit_code = -1;
    char *pathname;

    // Make sure envar actually exists
    pathname = getenv("FTOK_PATH");

    if (!pathname) {
        // fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        pathname=(char*)FTOK_PATH;
    }
    printf("identity of the file named FTOK_PATH=%s\n", pathname);

    // ftok togenerate unique key 
    key_t key = ftok(pathname,FTOK_PROJ_ID);     
    if ( key == -1 )
    {
        printf("main: ftok() for shm failed\n");
        return -1;
    }

    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    if (shmid == -1)
    {
    	printf("main: shmget() failed\n");
    	return -1;
    }  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
    if ( str==NULL )
    {
       printf("main: shmat() failed\n");
       return -1;
    }

    if (str) {
	if (strlen(str)>0) {
		printf("read %s\n",str);
        	cmp_code = strcmp( str, MemContents );
	}	
	else {
		printf("sorry nothing to read\n");
	  	cmp_code = -1;
	}
    	//detach from shared memory  
    	exit_code = shmdt(str); 
    
    	if (!exit_code) {
    		// destroy the shared memory 
    		exit_code = shmctl(shmid,IPC_RMID,NULL);
    	} 

    	if (!exit_code)
		exit_code = cmp_code; 
    }
    //printf("receiver exit_code %d\n",exit_code);
    return exit_code; 
} 
