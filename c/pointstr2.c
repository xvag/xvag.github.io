#include <stdio.h>
#include <string.h>

FILE *fp;
FILE *fo;

char chtable[];
//char *tokens[][10];
char *tokt[100];
char ch;
char *tok;
int main()
{
	fp=fopen("./input.txt","r");
	fo=fopen("./output.txt","w");
	if (fp==NULL) return 1;
	int i=0;
	int j=0;
	int k;
	int c=0;
	int count=0;
	
	tok=chtable;

	while((ch=fgetc(fp))!=EOF)
	{
		if (ch=='\n')
		{
			chtable[i++]='\0';
			c=puts(tok+count);
			tokt[j++]=tok+count;
			count+=c;
			//printf("%d\n",c);
		}else
			chtable[i++]=ch;
	}

	for (k=0;k<j;k++)
		printf("%s %c %d\n",tokt[k], *tokt[k], k);
	tokt[k] = chtable;
	printf("%s %s\n",tokt[k], chtable);

	for (k=0;k<count;k++)
		printf("%c",chtable[k]);

	printf("\n%s\n",chtable);



	/*
	int c=0;
	int count=0;
	
	tok=chtable;
	
	c=puts(tok+count);
	count+=c;
	printf("%d\n",c);

	c=puts(tok+count);
	count+=c;
	printf("%d\n",c);

	c=puts(tok+count);
	count+=c;
	printf("%d\n",c);

	//tok=gets(chtable);
	//printf("%s\n",tok);*/

	return 0;
}

