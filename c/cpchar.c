#include <stdio.h>

void main()
{
	int c;
	c = getchar();
	while (c!=EOF)
	{
		putchar(c);
		printf("\n%d %d\n", EOF, (getchar()!=EOF));
		c = getchar();
	}
}

	
