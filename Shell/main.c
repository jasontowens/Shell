#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "syntaxTree.c"
#define OK 0
#define BYE 1
#define ERROR 2

extern int yyparse();
extern char yytext[];
extern int yy_scan_string(const char *);

char line[500];
struct command* real_command;

int getCommand(){

	switch(yyparse()){
		case 0:
		
			printf("yayyy\n");

		case 1:
			printf("booo\n");
	}



}
int main( int argc, const char* argv[] )
{
	real_command = yylval.command;
	
	while(1)
	{	
		printf("nicebackend>");
		//fgets(line,sizeof(line),stdin);
		//yy_scan_string(line);
		if(yyparse()){
				printf("booo\n");
		}else{
				printf("yayyy\n");
		}
		//if(cool){
			//printf("%s\n", yylval);
			//printf("boo\n");

		//}else{
			//printf("yay\n");
		//}
	}
}