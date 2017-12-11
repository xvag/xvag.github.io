#include <stdio.h>

void main()
{
	int x;
	int i;

	for (x='a';x<='z';x++)
	printf("%d %c\n",x,x);

	for (i=0;i<=100;++i)
		printf("%d %c\n",i,i);
}
