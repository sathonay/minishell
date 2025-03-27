
#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

pid_t	fork_exec(char *cmd, char **env, int fdin, int fdout);

#endif
