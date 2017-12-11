#include <stdio.h>

static char *table[] = {"one","two","three","four","five"};

int main ()
{
	int i=0;

	while(1)
	{
		if (*table[i]=='\0') break;		
		printf("%s.\n",table[i++]);
	}
}

