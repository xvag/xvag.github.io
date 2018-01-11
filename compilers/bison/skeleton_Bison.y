/* ______________________________________________

Title:  ........... (bison skeleton)
Author:
Lab:
_________________________________________________

Perioxi diloseon C kodika syntaktikoy analyti 
(bibliothikes klp)
_________________________________________________*/

%{
#define RED "\x1B[31m"
#define BLU "\x1B[34m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE char *
int errorflag=0;

extern char * yytext;
void yyerror(char  const* s);
extern FILE *yyin;
extern int yylineno;
extern int yylex();
%}

/* _____________________________________________

       perioxi dilosis tokens 
________________________________________________*/
%error-verbose
%token NEWLINE FUNC
%token DECL_TYPE VAR STRING
%token INT FLOAT

/* _____________________________________________

      proairetiki perixi dilosis proteraiotitwn 
_________________________________________________*/

%left '(' ')'
%left '+' '-'
%left '*' '/'
%left NEG

/* ______________________________________________

       dilosi start conditions 
_________________________________________________*/

%start program


/* ______________________________________________

                  perioxi kanonwn 
_________________________________________________*/

%%

program: 
	| program codeline
	;

codeline: NEWLINE
	| decl NEWLINE {printf("\n### line[%d] ###\n\n", yylineno-1);}
	| assign NEWLINE {printf("\n### line[%d] ###\n\n", yylineno-1);}
	| func NEWLINE {printf("\n### line[%d] ###\n\n", yylineno-1);}
	| error NEWLINE {errorflag=1; yyerrok;}
	;

decl:	DECL_TYPE VAR {printf("\nDeclaration");}
	| DECL_TYPE assign {printf("\nDeclaration with assignment");}
	;

assign: VAR '=' expr {printf("\nExpression Assignment");}
	| VAR '=' func {printf("\nFunction with Assignment");}
	;

expr:	VAR
	| INT
	| FLOAT
	| STRING
	| expr '+' expr {printf("\nAddition");}
	;

func:	FUNC '(' VAR ')' {printf("\nPython Function on Variable");}
	| FUNC '(' STRING ')' {printf("\nPython Function on String");}
	;
%%



void yyerror(const char* msg)
{
	printf(RED"\nLine: %d FAILURE %s\n\n"RESET,yylineno,msg);
}

int main(int argc,char **argv)
{
	int i;
	if(argc == 2)
		yyin=fopen(argv[1],"r");
	else
		yyin=stdin; 

  if (yyparse()== 0 && errorflag == 0)
     fprintf(stderr, GRN"Successful parsing.\n"RESET);
  else
     fprintf(stderr, RED"error(s) found!\n"RESET);
  return 0;
}
