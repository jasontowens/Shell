#define MAXPIPES 25
typedef struct myPipe{
	COMMAND* command;
	int io[2];
}MYPIPE;

typedef struct pipingTable{
	MYPIPE pipes[MAXPIPES];
	int numPipes;
}PIPINGTABLE;

extern PIPINGTABLE* pipingTable;
int performPipe();
