#include <stdlib.h>
#include "syntaxTree.h"
#include "pipe.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

PIPINGTABLE* pipingTable;

int performPipe(){
	int p[2];
	pid_t pid;
	int fd_in = 0;
	for(int i = 0; i!= pipingTable->numPipes; ++i){
		pipe(p);
		char* infileName = myCommand->inputFile;
		char* outfileName = myCommand->outputFile;
		if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }else if (pid == 0){

          dup2(fd_in, 0);
          if(i == 0){
          	 if (file_input == 1) { //if '<' char was found in string inputted by user
			  	//printf("inputbitch\n");
			    if( access( infileName, F_OK ) == -1 ) {
    				//printf("That file doesn't exist\n");
       				exit(EXIT_FAILURE);
				}
			    int fd0 = open(infileName, O_RDONLY, 0);
			    
			    dup2(fd0, STDIN_FILENO);
			    close(fd0);
			    
			}

          }
         if(i != pipingTable->numPipes - 1){
          	 dup2(p[1], 1);
          }







		 if(i == pipingTable->numPipes - 1){
          	 
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
          }





         
          close(p[0]);
       
          pipingTable->pipes[i].command->arguments->args[ pipingTable->pipes[i].command->numArgs] = NULL;
          performPipingCommand(pipingTable->pipes[i].command);
          //execvp(pipingTable->pipes[i].command->arguments->args[0], pipingTable->pipes[i].command->arguments->args);
          printf("Unknown Command\n");
          exit(EXIT_FAILURE);
        }else{
          wait(NULL);
          close(p[1]);
          fd_in = p[0];
        }
	}

return 1;
}