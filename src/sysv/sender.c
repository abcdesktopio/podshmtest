#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include "shmem.h"
using namespace std; 


int main() 
{ 
    printf("sender starts\n");

    char *pathname;

    // Make sure envar actually exists
    pathname = getenv("FTOK_PATH");
    
    if (!pathname) {
        pathname=(char*)FTOK_PATH;
    }

    printf("identity of the file named FTOK_PATH=%s\n", pathname);

    int exit_code = -1;
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
	strcpy(str, MemContents );
    	//detach from shared memory 
    	exit_code = shmdt(str);
    	if (!exit_code) {
		printf("sending success %s", MemContents);
	}
    }
    return exit_code; 
}
