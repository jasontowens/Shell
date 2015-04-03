#define MAXARGS 100
typedef struct comargs{
	char* args[MAXARGS];
}ARGUMENTS;

typedef struct command{
	char* commandName;
	ARGUMENTS* arguments;
}COMMAND;



int performCommand(COMMAND* myLocalCommand);
extern COMMAND* myCommand;