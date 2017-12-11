#include <stdio.h>
#include <string.h>

void return_input (void)
{
	char array[30];

	scanf("%s",array);
	printf("%s\n", array);
}

int main()
{
	return_input();
	return 0;
}
