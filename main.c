#include "shell.h"

int main()
{
	while (1)
	{
		char * input = readline("|>");
		printf("%s", input);
		free(input);
	}
}
