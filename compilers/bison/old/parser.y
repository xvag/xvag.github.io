   
%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE char*
int errorflag=0;


extern int yylineno;
extern char * yytext;
%}

%error-verbose

%token IDENTIFIER STRING INTEGER FLOAT NEWLINE
%token DELETE PRINT

%token IDENT_ERROR ZERO_START_ERROR


%left '+' '-'
%left '*' '/' 

%start Input

%%

Input:
   /* empty line */
     | Input Line
	;

Line:
     NEWLINE
     | Expression NEWLINE 
     | error NEWLINE { errorflag=1; yyerrok; } /* unknown syntax error */
	
     ;

/*oi syntaktikoi kanones pou endexetai na anagnoristoun*/
Expression: atom {$$=$1;}
	  | simple_stmt {$$=$1;}
	  | lexical_errors  /* error caused by lexical analysis */
	;

atom: IDENTIFIER | STRING | INTEGER | FLOAT 
	;

simple_stmt: assignment_stmt
	   | del_stmt
	   | print_stmt
	;

len_stmt: LEN '(' IDENTIFIER ')' 
	   | /* add specific error rules*/
	;
	 

print_stmt: PRINT '(' STRING ')'
	   | /* add specific error rules*/
	;

input_stmt: INPUT '(' STRING ')'
	   | /* add specific error rules*/
	;

lexical_errors: 
	DELETE '(' error   NEWLINE{ printf("%s",$1);printf		("\tIDENTIFIER error!\n")
	| PRINT '(' error  NEWLINE{ printf("%s",$1);printf		("\tatom error!\n"); 
	;

%%

//h synarthsh yyerror pou emfanizei mhnyma sth periptwsh eyreshs kapoiou lathous

int yyerror( char  const*s) {
  printf("Line: %d FAILURE %s\n",yylineno-1,s);
}

FILE *yyin;

int main(int argc,char **argv)
{
	int i;
	if(argc == 2)
		yyin=fopen(argv[1],"r");
	else
		yyin=stdin; 

  if (yyparse()== 0 && errorflag == 0)
     fprintf(stderr, "Successful parsing.\n");
  else
     fprintf(stderr, "error(s) found!\n");
  return 0;
}

