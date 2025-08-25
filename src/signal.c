#include "shell.h"

void	cmd_sigint(int signum)
{
	(void)signum;
	printf("\n");
}

void	main_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	main_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	signals_main(void)
{
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_cmd(void)
{
	signal(SIGINT, cmd_sigint);
	signal(SIGQUIT, cmd_sigint);
}