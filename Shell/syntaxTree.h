#define MAXARGS 100
#define MAXALIAS 100
typedef struct comargs{
	char* args[MAXARGS];
}ARGUMENTS;

typedef struct command{
	ARGUMENTS* arguments;
	int numArgs;
}COMMAND;

typedef struct aliasTable{
	char* names[MAXALIAS][2];
	int numAlias;
}ALIASTABLE;




int performCommand(COMMAND* myLocalCommand);
//int lookUp(command);
extern ALIASTABLE* _aliasTable;
extern COMMAND* myCommand;
