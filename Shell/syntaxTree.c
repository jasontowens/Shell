#include <stdlib.h>
#include "syntaxTree.h"
#include  <string.h>
#include  <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
COMMAND* myCommand;

 int performCommand(COMMAND* myLocalCommand){
 	char* command = myLocalCommand->commandName;
 	if(strcmp(command,"bye") == 0){
 		return 0;
 	}
 	if(strcmp(command,"cd") == 0){
 		int success = chdir(myLocalCommand->arguments->args[0]); 
 		//printf("%d\n",success);
 	}
 	if(strcmp(command,"ls") == 0){
 		char* path = getenv("PATH");
 		

 		myLocalCommand->arguments->[args0] = "bin/ls";
 		myLocalCommand->arguments->args[1] = NULL;

	  pid_t  child;
	  int    cstatus;  /* Exit status of child. */
	  pid_t  c;        /* Pid of child to be returned by wait. */
	  
	  if ((child = fork()) == 0) { /* Child process. */
	     //printf("Child: PID of Child = %ld\n", (long) getpid());
	     execv("/bin/ls",myLocalCommand->arguments->args); 
	     /* If the child process reaches this point, then  */
	     /* execvp must have failed.                       */
	     fprintf(stderr, "Child process could not do execvp.\n");
	exit(1); }
	  else { /* Parent process. */
	     if (child == (pid_t)(-1)) {
	        //fprintf(stderr, "Fork failed.\n"); exit(1);
	     }
	     else {
	        c = wait(&cstatus); /* Wait for child to complete. */
	       //printf("Parent: Child  %ld exited with status = %d\n",
	               //(long) c, cstatus);
	} 
}

 	}
 	return 1;
 	 
 }