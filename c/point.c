#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

FILE *fp;
char ch;
char one[10]="one";
char two[10]="two";
char three[10]="three";

char variable[100];
char *tokentable[10][100];

int i=0,j=0,c,k;

int main()
{

	fp=fopen("./input.txt","r");
	if (fp==NULL) return 1;

	while((ch=fgetc(fp))!=EOF)
	{
		variable[i++]=ch;
		if(ch=='\n')
		{	
			k=0;
			variable[i+1]='\0';
			tokentable[1][j]=&variable[i-k];
		}
	}
	

	for (c=0;c<=i;c++)
	//	printf("%c",variable[c]);
		printf("%s \n",tokentable[1][c]);


/*
	strtable[1][0]=&one[0];
	strtable[1][1]=&two[0];
	strtable[1][2]=&three[0];
	for(i=0;i<3;i++)
		printf("%s\n",strtable[1][i]);

	strtable[1][0]=strcpy(*strtable[1],one);
	strtable[1][1]=strcpy(*strtable[1],two);
	strtable[1][2]=strcpy(*strtable[1],three);
	for(i=0;i<3;i++)
		printf("%s %s\n",*strtable[1][i], strtable[1][i]);*/
	
return 0;
}
