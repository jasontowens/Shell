#include <stdlib.h>
#include "syntaxTree.h"
#include  <string.h>
#include  <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
COMMAND* myCommand;
ALIASTABLE* _aliasTable;

int lookUp(char* argument){
	int i = 0;
 	while(i != _aliasTable->numAlias){
 		if(strcmp(argument,_aliasTable->names[i][0]) == 0){
 			return i;
 		}else if(strcmp(argument,_aliasTable->names[i][1]) == 0){
 			//printf("sdkgf\n");
 			return -2;
 		}
 		++i;
 	}

 	return -1;
}

 int fixArgumentsWithAlias(){
 	int i = 0;
 	while(i != myCommand->numArgs){
 		int number = lookUp(myCommand->arguments->args[i]);
 		if(number == -2){
 			return 0;
 		}else if(number != -1){
 			myCommand->arguments->args[i] = _aliasTable->names[number][1];
 		}
 		++i;
 	}
 	return 1;
 }

 int performCommand(COMMAND* myLocalCommand){
 	myLocalCommand->arguments->args[myLocalCommand->numArgs] = NULL;
 	int cont = fixArgumentsWithAlias();
 	if(!cont){
 		return 1;
 	}
 	//printf("%d\n",myLocalCommand->numArgs);
 	char* command = myLocalCommand->arguments->args[0];
 	//printf("%s\n",command);
 	if(strcmp(command,"bye") == 0){
 		return 0;
 	}else if(strcmp(command,"cd") == 0){
 		int success = chdir(myLocalCommand->arguments->args[1]); 
 		//printf("%d\n",success);
 	}else if(strcmp(command,"setenv") == 0){
 		int success = chdir(myLocalCommand->arguments->args[1]); 
 		//printf("%d\n",success);
 	}else if(strcmp(command,"printenv") == 0){
 		int success = chdir(myLocalCommand->arguments->args[1]); 
 		//printf("%d\n",success);
 	}else if(strcmp(command,"unsetenv") == 0){
 		int success = chdir(myLocalCommand->arguments->args[1]); 
 		//printf("%d\n",success);
 	}else if(strcmp(command,"alias") == 0){
 		_aliasTable->names[_aliasTable->numAlias][0] = myLocalCommand->arguments->args[1];
 		_aliasTable->names[_aliasTable->numAlias][1] = myLocalCommand->arguments->args[2];
 		_aliasTable->numAlias++;
 		
 	}else if(strcmp(command,"unalias") == 0){
 		int success = chdir(myLocalCommand->arguments->args[1]); 
 		//printf("%d\n",success);
 	}else{
 		
 
		pid_t  child;
		int    cstatus;  /* Exit status of child. */
		pid_t  c;        /* Pid of child to be returned by wait. */

		  if ((child = fork()) == 0) { /* Child process. */
		     //printf("Child: PID of Child = %ld\n", (long) getpid());
		     execvp(myLocalCommand->arguments->args[0],myLocalCommand->arguments->args);
		     fprintf(stderr, "Child process could not do execvp.\n");
			 exit(1); 
			}
		  else {
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


 //setenv("PATH","xxx",1);
 		//printf("%s\n",getenv("PATH"));
 		// char** path = (char**)malloc(sizeof(char*));
 		// char* path1 = getenv("PATH");
 		// char* token;
 		// printf("%s\n",path1);
 		// token = strtok(path1,":");
 		// int i = 0;
 		// while(token!=NULL){
 		// 	path[i] = token;
 		// 	token = strtok(NULL,":");
 		// 	printf("%s\n",path[i]);
 		// 	++i;
 			
 		// }

 		// char *buff = malloc(200 * sizeof(char));
 		// strcpy(buff,"");
 		// char* myPath = path[3];
 		// char* slash = "/";
 		// char* argument = myLocalCommand->arguments->args[0];
 		// char* buffer;
 		// printf("%s\n",path[2]);
 		// buffer = strcat(buff,myPath);
 		// printf("hey2\n");
 		// buffer = strcat(buff,slash);
 		// buffer =strcat(buff,argument);
 		// myLocalCommand->arguments->args[0] = buffer;
 		// access(buff,X_OK);
 		// free(buff);
 
 
