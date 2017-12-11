#include <stdio.h>

char ch;
char chtable[100];
char *chptr;

FILE *fp;
FILE *fo;

int i=0;


int main()
{
	fp=fopen("./input.txt","r");
	fo=fopen("./output.txt","w");
	if (fp==NULL) return 1;

	while((ch=fgetc(fp))!=EOF)
	{
		chtable[i]=ch;
		i++;
		if(ch=='\n')
			chtable[i]='\0';
	}
	
	chptr=chtable;
	
	fputs(chptr,fo);

	return 0;
}

