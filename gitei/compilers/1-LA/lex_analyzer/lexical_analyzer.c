#include <stdio.h>

enum State {Q0, O0, O1, O2, O3, O4, O5, O6, I0, I1, F0, F1, F2, F3, V0, S0, S1, S2, C0, C1,\
       	E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, GOOD, FOUND, BAD};
typedef enum State State;

char ch;
FILE *fp;
FILE *fo;
int counter, lcounter, token=0, btoken=0, flag;

void scanner();

void dbg(char* prn)
{
	printf("%s", prn);
}

void avoidblanks()
{
	int wc=0;
	while(1)
	{
		if(ch=='\n')lcounter+=1;
		if((ch!=' ')&&(ch!='\n')&&(ch!='\t'))
		{
			printf("%d whites, line: %d",wc,lcounter);
			break;
		}
		ch=fgetc(fp);
		if(ch!=EOF)wc+=1;
	}
}

void avoidchars()
{
	int uc=0;
	printf("%c",ch);
	ch=fgetc(fp);

/*	while (ch!=EOF)
	{
		if((ch!=' ')&&(ch!='\n')&&(ch!='\t'))
		{
			ch=fgetc(fp);
			if(ch!=EOF)uc+=1;
		}
		else
		{
			printf("%d unknown, line:%d\n",uc,lcounter);
			break;
		}
	}*/
}


int main(int argc, char** argv)
{
	fp=fopen("./input.txt","r");
	fo=fopen("./output.txt","w");

	if (fp==NULL) return 1;

	lcounter=1;
	ch=fgetc(fp);

	while (ch!=EOF)
	{
		counter=0;
		if((ch==' ')||(ch=='\n')||(ch=='\t'))
		{
			printf("\n[SKIP white spaces]: ");
			flag=0;
			avoidblanks();
		}
		else if ((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch=='+')||(ch=='=')||(ch=='-')||(ch=='*')||(ch=='%')||(ch=='.')||(ch=='\'')||(ch=='\"'))
		{
			//printf("\n");
			flag=0;
			scanner(); continue;
		}
		else
		{
			//dbg("Skip unknown characters: ");
			if (flag==0) printf("\n[SKIP Unknown characters]: ");
			avoidchars();
			flag=1;
		}
	}
	
	printf("\n");
	fclose(fp);
	fclose(fo);
	return 0;
}

void scanner()
{
	dbg("\nScanning.. ");
	State currSt=Q0;
	State prevSt;
	while(1)
	{
		switch (currSt)
		{
			case Q0:
				{
					dbg(" Q0");
					prevSt=Q0;
					if (ch=='/'){currSt=O3; break;}
					else if (ch=='*'){currSt=O2; break;}
					else if (ch=='%'){currSt=O1; break;}
					else if (ch=='+'||ch=='-'){currSt=O0; break;}
					else if (ch=='='){currSt=O6; break;}
					else if (ch=='.'){currSt=E1; break;}
					else if (ch=='0'){currSt=I0; break;}
					else if ((ch>='1')&(ch<='9')){currSt=I1; break;}
					else if ((ch>='a'&&ch<='z')||(ch=='_')){currSt=V0; break;}
					else if (ch=='\''){currSt=E5; break;}
					else if (ch=='\"'){currSt=E4; break;}
					else if (ch=='#'){currSt=C0; break;}
					else {currSt=BAD; break;}
				}
			case O0:
				{
					dbg(" O0");
					prevSt=O0;
					if (ch=='0'){currSt=I0; break;}
					else if ((ch>='1')&&(ch<='9')){currSt=I1; break;}
					else if (ch=='.'){currSt=E1; break;}
					else if (ch=='='){currSt=O6; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O1:
				{
					dbg(" O1");
					if (ch=='='){currSt=O6; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O2:
				{
					dbg(" O2");
					if (ch=='='){currSt=O6; break;}
					else if (ch=='*'){currSt=O4; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O3:
				{
					dbg(" O3");
					if (ch=='='){currSt=O6; break;}
					else if (ch=='/'){currSt=O5; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O4:
				{
					dbg(" O4");
					if (ch=='='){currSt=O6; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O5:
				{
					dbg(" O5");
					if (ch=='='){currSt=O6; break;}
					else {currSt=GOOD; token=1; break;}
				}
			case O6:
				{
					dbg(" O6");
					currSt=GOOD; token=1; break;
				}
			case I0:
				{
					dbg(" I0");
					if ((ch>='0')&&(ch<='9')){currSt=E0; break;}
					else if (ch=='.'){currSt=F0; break;}
					else {currSt=GOOD; token=2; break;}
				}
			case I1:
				{
					dbg(" I1");
					if ((ch>='0')&&(ch<='9')){currSt=I1; break;}
					else if (ch=='.'){currSt=F0; break;}
					else {currSt=GOOD; token=2; break;}
				}
			case F0:
				{
					dbg(" F0");
					if ((ch=='e')||(ch=='E')){currSt=E2; break;}
					else if ((ch>='0')&&(ch<='9')){currSt=F1; break;} 	//katargisi F2-ensomatosi me F1
					else {currSt=GOOD; token=3; break;}
				}
			case F1:
				{
					dbg(" F1");
					if ((ch>='0')&&(ch<='9')){currSt=F1; break;}
					else if ((ch=='e')||(ch=='E')){currSt=E2; break;}
					else {currSt=GOOD; token=3; break;}
				}
			case F2:
				{
					dbg(" F2");						//afto einai to F3 sto fsm
					if ((ch>='0')&&(ch<='9')){currSt=F2; break;}
					else {currSt=GOOD; token=3; break;}
				}
			case V0:
				{
					dbg(" V0");
					if ((ch>='a'&&ch<='z')||(ch=='_')){currSt=V0; break;}
					else {currSt=GOOD; token=4; break;}
				}
			case S0:
				{
					dbg(" S0");
					currSt=GOOD; token=5; break;
				}
			case S1:
				{
					dbg(" S1");
					currSt=GOOD; token=5; break;
				}
			case S2:
				{
					dbg(" S2");
					if(ch=='\"'){currSt=E7; break;}
					else {currSt=GOOD; token=5; break;}
				}
			case C0:
				{
					dbg(" C0");
					if ((ch>='a')&&(ch<='z')){currSt=C0; break;}
					else {currSt=GOOD; token=6; break;}
				}
			case C1:
				{
					dbg(" C1");
					if ((ch>='a')&&(ch<='z')){currSt=E7; break;}
					else if (ch=='\"'){currSt=C1; break;}
					else {currSt=GOOD; token=6; break;}
				}
			case E0:
				{
					dbg(" E0");
					if ((ch>='0')&&(ch<='9')){currSt=E0; break;}
					else if (ch=='.'){currSt=F0; break;}
					else {currSt=BAD; btoken=1; break;}
				}
			case E1:
				{
					dbg(" E1");
					if ((ch>='0')&&(ch<='9')){currSt=F1; break;}
					else {currSt=BAD; btoken=2; break;}
				}
			case E2:
				{
					dbg(" E2");
					if ((ch>='0')&&(ch<='9')){currSt=F2; break;}
					else if ((ch=='+')||(ch=='-')){currSt=E3; break;}
					else {currSt=BAD; btoken=3; break;}
				}
			case E3:
				{
					dbg(" E3");
					if ((ch>='0')&&(ch<='9')){currSt=F2; break;}
					else {currSt=BAD; btoken=4; break;}
				}
			case E4:
				{
					dbg(" E4");
					if (ch=='\"'){currSt=S2; break;}
					else if ((ch>='a')&&(ch<='z')){currSt=E6; break;}
					else {currSt=BAD; btoken=5; break;}
				}
			case E5:
				{
					dbg(" E5");
					if ((ch>='a')&&(ch<='z')){currSt=E5; break;}  //problem
					else if (ch=='\''){currSt=S0; break;}
					else {currSt=BAD; btoken=6; break;}
				}
			case E6:
				{
					dbg(" E6");
					if ((ch>='a')&&(ch<='z')){currSt=E6; break;}
					else if (ch=='\"'){currSt=S1; break;}
					else {currSt=BAD; btoken=7; break;}
				}
			case E7:
				{
					dbg(" E7");
					if ((ch>='a')&&(ch<='z')||(ch=='\n')){currSt=E7; break;}
					else if (ch=='\"'){currSt=E8; break;}
					else {currSt=BAD; btoken=8; break;}
				}
			case E8:
				{
					dbg(" E8");
					if ((ch>='a')&&(ch<='z')||(ch=='\n')){currSt=E7; break;}
					else if (ch=='\"'){currSt=E9; break;}
					else {currSt=BAD; btoken=9; break;}
				}
			case E9:
				{
					dbg(" E9");
					if ((ch>='a')&&(ch<='z')||(ch=='\n')){currSt=E7; break;}
					else if (ch=='\"'){currSt=C1; break;}
					else {currSt=BAD; btoken=8; break;}
				}
			case GOOD:
				{
					dbg(" ---> ");
					currSt=FOUND;
					if(token==1)
						printf("line %d: <OPERATOR> %d chars",lcounter,counter);
					else if(token==2)
						printf("line %d: <INTEGER> %d chars",lcounter,counter);
					else if(token==3)
						printf("line %d: <FLOAT> %d chars",lcounter,counter);
					else if (token==4)
						printf("line %d: <VARIABLE> %d chars",lcounter,counter);
					else if (token==5)
						printf("line %d: <STRING> %d chars",lcounter,counter);
					else if (token==6)
						printf("line %d: <COMMENT> %d chars",lcounter,counter);
					printf("\n");
					break;
				}
			case BAD:
				{
					printf("BAD: line=%d, chars=%d\n",lcounter,counter);
					break;
				}
			case FOUND:
				{
					break;
				}
		}
		if ((currSt==FOUND)||(currSt==BAD)){break;}

		if (currSt!=GOOD){ch=fgetc(fp);counter++;}
	}
}
