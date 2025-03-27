#include "shell.h"

int main()
{
	while (1)
	{
		char *input = readline("|>");
		printf("%s\n", input);
		char ** args = ft_split(input, ' ');
		
		free(input);
		free_str_array(args);
	}
}
