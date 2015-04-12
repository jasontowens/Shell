/* alias.h -- structure definitions. */

/* Copyright (C) 1987-2009 Free Software Foundation, Inc.

   This file is part of GNU Bash, the Bourne Again SHell.

   Bash is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Bash is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Bash.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "stdc.h"
#include "syntaxTree.h"
#include "hashlib.h"

typedef struct alias {
  char *name;
  char *value;
  char flags;
  int glob;
} alias_t;

/* Values for `flags' member of struct alias. */
#define AL_EXPANDNEXT		0x1
#define AL_BEINGEXPANDED	0x2

/* The list of known aliases. */
extern int numAlias;
int addMyAlias(char* name , char* value, int globbed);
void printAlias();
void fixAlias(COMMAND* command);
char* fixWord(char* word);
extern HASH_TABLE *aliases;
extern void initialize_aliases();
extern alias_t** all_aliases();

/* Scan the list of aliases looking for one with NAME.  Return NULL
   if the alias doesn't exist, else a pointer to the alias. */
extern alias_t *find_alias __P((char *));

/* Return the value of the alias for NAME, or NULL if there is none. */
extern char *get_alias_value __P((char *));

/* Make a new alias from NAME and VALUE.  If NAME can be found,
   then replace its value. */
extern void add_alias __P((char *, char *, int));

/* Remove the alias with name NAME from the alias list.  Returns
   the index of the removed alias, or -1 if the alias didn't exist. */
extern int remove_alias __P((char *));


