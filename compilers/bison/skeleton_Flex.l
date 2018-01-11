/* ______________________________________________

Title:  ........... (flex skeleton as a lexical analisi function)
Author:
Lab:



_________________________________________________

      proairetiki perixi dilosis start katastaseWn 
_________________________________________________

*/



%option noyywrap

 /*_________________________________________________
  Kwdikas C gia orismo twn apaitoumenwn header files 
  kai twn metablhtwn
 _________________________________________________*/

%{

#define YYSTYPE double

#include "skeleton_Bison.tab.h"  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define BLU "\x1B[34m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"

int lcounter=1, counter=0, space=0;

void prn(char *s);
%}

/* _____________________________________________
 
                  perioxi orismWn  
________________________________________________*/

EXP [eE]
SIGN [+-]
DIGIT [0-9]
NOZERO [1-9]
LOW [a-z]
CAP [A-Z]
VAR [a-zA-Z_][a-zA-Z_0-9]*

OP "+"|"-"|"*"|"/"|"%"|"**"|"//"
ASSIGN_OP "+="|"-="|"*="|"/="|"%="|"**="|"//="

DECL_TYPE "int"|"float"|"str"
FUNC "type"|"len"|"print"|"input"
SPECIAL ";"|","|"["|"]"|"{"|"}"
ALL .


 /* ______________________________________________

                  perioxi kanonwn 
 _________________________________________________*/

%%

"#".*|"\""{3}[\xA\x20-\x7E]*"\""{3} {
//printf(YEL"Comment"RESET"(line %d): %s\n", lcounter, yytext);
}

{FUNC} {printf("%s", yytext); return FUNC; }

"(" { printf("("); return '('; }
")" { printf(")"); return ')'; }
"," { printf(","); return ','; }
"=" { printf("="); return '='; }

{OP} {
printf("%s", yytext); 
return OP; }

{ASSIGN_OP} {
printf("%s", yytext);
return ASSIGN_OP;}

{DECL_TYPE} {printf("%s", yytext); return DECL_TYPE;}

{SPECIAL} {
printf("Special(line %d): %s\n",lcounter, yytext);}

{SIGN}?(0|{NOZERO}{DIGIT}*) {
printf("%s",yytext);
return INT;}

{SIGN}?({DIGIT}+"."{DIGIT}*|"."{DIGIT}+)({EXP}{SIGN}?{DIGIT}+)? {
printf("%s",yytext);
return FLOAT;}

{SIGN}?\.{EXP}?{SIGN}?{DIGIT}* {
printf(RED"\n Lexical Error: Illegal Float"RESET"(line:%d): %s",lcounter,yytext);};

"\"".*"\""|"'".*"'" {
printf("%s", yytext); 
return STRING; }

("\""[^\"\n]*)|("'"[^'\n]*) {
printf(RED"\n Lexical Error: Illegal String"RESET"(line:%d): %s", lcounter, yytext);}

{VAR} {
printf("%s", yytext); 
return VAR;}

{DIGIT}+{VAR} {
printf(RED"\n Lexical Error: Illegal Variable name"RESET"(line:%d): %s", lcounter, yytext);}

\n { yylineno++; lcounter++; return NEWLINE; }
" " { printf("%s", yytext); space++; }
<<EOF>>		{ printf("\n#FILE ENDED\n%d lines read\n", yylineno-1); return 0; };

. { printf("unscanned %s", yytext); counter++; }

%%

void prn(char *s)
{
	printf("\n\t%s(line %d): %s ", s, yylineno, yytext);
	return;
}
