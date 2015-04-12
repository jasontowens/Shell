#include <stdlib.h>
#include "alias.h"
#include "syntaxTree.h"

#include  <string.h>
#include  <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
COMMAND* myCommand;
COMMAND* myGlobCommand;
int type;
int globCommand;
int file_input;
int file_output;
extern char **environ;

int performGlobedCommand(){
printf("sadf\n");
		char* command = myGlobCommand->arguments->args[0];
		printf("%s\n",myGlobCommand->arguments->args[0]);
		if(strcmp(command,"unalias") == 0){
	 		if(remove_alias(myGlobCommand->arguments->args[1]) == -1){
	 			printf("This alias does not exist\n");
	 		}
 			return 1;
 		}else if(strcmp(command,"alias") == 0){
 			if(myGlobCommand->numArgs == 1){
 				printAlias();
 				return 1;
 			}
 			addMyAlias(myGlobCommand->arguments->args[1],myCommand->arguments->args[2],1);
 			return 1;
 		}
 		char words[500];
 		char* arg;
 		for(int i = 0; i!= myGlobCommand->numArgs; ++i){
 			printf("%s\n",myGlobCommand->arguments->args[i]);
 			if(fixWord(myGlobCommand->arguments->args[i]) != NULL){
 				arg = fixWord(myCommand->arguments->args[i]);
 			}else{
 				arg = myGlobCommand->arguments->args[i];
 			}
 			strcat(words,arg);
 			strcat(words," ");
 		}


		pid_t  child;
		int    cstatus;  /* Exit status of child. */
		pid_t  c;        /* Pid of child to be returned by wait. */

		if ((child = fork()) == 0) { 
			char* yo[4] = {"sh","-c",words,NULL};
			execvp(yo[0],yo);
			printf("Unknown Command\n");
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
	
	return 1;
}


 int performCommand(COMMAND* myLocalCommand){//the alias stuff should be called before this
 	myLocalCommand->arguments->args[myLocalCommand->numArgs] = NULL;
 	char* command = myLocalCommand->arguments->args[0];

 	if(strcmp(command,"unalias") == 0){
 		if(remove_alias(myLocalCommand->arguments->args[1]) == -1){
 			printf("This alias does not exist\n");
 		}
 		return 1;
 	}else if(strcmp(command,"alias") == 0){
 		if(myLocalCommand->numArgs == 1){
 			printAlias();
 			return 1;
 		}
 		addMyAlias(myLocalCommand->arguments->args[1],myLocalCommand->arguments->args[2],0);
 		return 1;
 	}
 	//printf("%s\n",command);
 	if(fixAlias(myLocalCommand) == -2){
 		performGlobedCommand();
 		return 1;
 	}
 	
 	if(strcmp(command,"bye") == 0){
 		//printf("bye\n");
 		return 0;
 	}else if(strcmp(command,"cd") == 0){
 		char* yo = myLocalCommand->arguments->args[1];
 		if(myLocalCommand->numArgs == 1){
 			yo = getenv("HOME");
 		}
 		int success = chdir(yo); 
 		if(success == -1){
 			printf("Changing Directories Failed\n");
 		}
 	}else if(strcmp(command,"setenv") == 0){
 		int yay = setenv(myLocalCommand->arguments->args[1],myLocalCommand->arguments->args[2],1);
 	}else if(strcmp(command,"unsetenv") == 0){
 		unsetenv(myLocalCommand->arguments->args[1]);
 	}else{
 		
		pid_t  child;
		int    cstatus;  /* Exit status of child. */
		pid_t  c;        /* Pid of child to be returned by wait. */

		  if ((child = fork()) == 0) { /* Child process. */
		     char* infileName = myLocalCommand->inputFile;
		     char* outfileName = myLocalCommand->outputFile;

			  if (file_input == 1) { //if '<' char was found in string inputted by user
			  	//printf("inputbitch\n");
			    if( access( infileName, F_OK ) == -1 ) {
    				printf("That file doesn't exist\n");
       				exit(EXIT_FAILURE);
				}
			    int fd0 = open(infileName, O_RDONLY, 0);
			    
			    dup2(fd0, STDIN_FILENO);
			    close(fd0);
			    
			}

			if (file_output == 1) { //if '>' was found in string inputted by user
				int fd1;
				//printf("yoo\n");
				//printf("%d\n",file_output);
				if( access( outfileName, F_OK ) == -1 ) {
    				fd1 = creat(outfileName, 0644);
				}else{
					fd1 = open(outfileName, O_WRONLY, 0);
				}
			    
			    dup2(fd1, STDOUT_FILENO);
			    close(fd1);
			    
			 }

			 
			 //printf("thenoom%s\n",myLocalCommand->arguments->args[0]);
			// printf("thenoom%s\n",myLocalCommand->arguments->args[1]);
			 // printf("thenoom%s\n",myLocalCommand->arguments->args[2]);
		     execvp(myLocalCommand->arguments->args[0],myLocalCommand->arguments->args);
		     printf("Unknown Command\n");
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

 int performPipingCommand(COMMAND* myLocalCommand){
 	myLocalCommand->arguments->args[myLocalCommand->numArgs] = NULL;
 	char* command = myLocalCommand->arguments->args[0];
 	if(strcmp(command,"unalias") == 0){
 		if(remove_alias(myLocalCommand->arguments->args[1]) == -1){
 			printf("This alias does not exist\n");
 		}
 		return 1;
 	}else if(strcmp(command,"alias") == 0){
 		if(myLocalCommand->numArgs == 1){
 			printAlias();
 			return 1;
 		}
 		addMyAlias(myLocalCommand->arguments->args[1],myLocalCommand->arguments->args[2],0);
 		return 1;
 	}
 	fixAlias(myLocalCommand);
 	
 	if(strcmp(command,"bye") == 0){
 		printf("bye\n");
 		return 0;
 	}else if(strcmp(command,"cd") == 0){
 		char* yo = myLocalCommand->arguments->args[1];
 		if(myLocalCommand->numArgs == 1){
 			yo = getenv("HOME");
 		}
 		int success = chdir(yo); 
 		if(success == -1){
 			printf("Changing Directories Failed\n");
 		}
 	}else if(strcmp(command,"setenv") == 0){
 		int yay = setenv(myLocalCommand->arguments->args[1],myLocalCommand->arguments->args[2],1);
 	}else if(strcmp(command,"unsetenv") == 0){
 		unsetenv(myLocalCommand->arguments->args[1]);
 	}else{



 	
	execvp(myLocalCommand->arguments->args[0],myLocalCommand->arguments->args);
	printf("Unknown Command");
			
	}
	 	return 1;	
 }


 
 
