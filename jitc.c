/**
 * Tony Givargis
 * Copyright (C), 2023
 * University of California, Irvine
 *
 * CS 238P - Operating Systems
 * jitc.c
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dlfcn.h>
#include "system.h"
#include "jitc.h"

/**
 * Needs:
 *   fork()
 *   execv()
 *   waitpid()
 *   WIFEXITED()
 *   WEXITSTATUS()
 *   dlopen()
 *   dlclose()
 *   dlsym()
 */

/* research the above Needed API and design accordingly */

int jitc_compile(const char *input, const char *output)
{
    int pid=fork();
    if(pid==0)
    {
        const char *gcc_path = "/usr/bin/gcc";
        char *cmd[] = {"gcc", "-fPIC", "-shared", (char *)input, (char *)output, NULL};
        execv(gcc_path, cmd); 
        perror("execv"); 
        _exit(1); 
        return -1;
    }
    else
    {
        int status;
        waitpid(pid,&status,0);
        
         // Wait for the child to terminate

        if (WIFEXITED(status)) {
            
            int exit_status = WEXITSTATUS(status);
            printf("Child exited with status: %d\n", exit_status);
        }
        
        return 0;
    }
}

struct jitc *jitc_open(const char *sharedlib)
{
    void *handle = dlopen(sharedlib, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading .so file: %s\n", dlerror());
        return -1;//find out error return
    }
    return handle;

}

long jitc_lookup(struct jitc *jitc, const char *symbol)
{
     double (*evaluate)(void);
   return *(void **)(&evaluate) = dlsym((void*)jitc, "evaluate");
 
}

void jitc_close(struct jitc *jitc)
{
    
        dlclose((void *)jitc);
       
}
    