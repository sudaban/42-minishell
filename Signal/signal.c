#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);  // ctrl-C
	signal(SIGQUIT, SIG_IGN);       // ctrl-D
}