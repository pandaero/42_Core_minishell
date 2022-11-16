// Program broadcasts PID to listen for signals.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void	sigone(int sig)
{
	printf("Received SIGUSR1 %d.\n", sig);
}

void	sigtwo(int sig)
{
	printf("Received SIGUSR2 %d.\n", sig);
}

void	sigstop(int sig)
{
	printf("Received SIGSTOP %d.\n", sig);
}

void	sigquit(int sig)
{
	printf("Received SIGQUIT %d.\n", sig);
}

void	sigint(int sig)
{
	printf("Received SIGINT %d.\n", sig);
}

void	sigkill(int sig)
{
	printf("Received SIGKILL%d.\n", sig);
}

int	main(void)
{
	int		*stat;
	//pid_t	pid;
	//pid = getpid();
	//printf("PID: %d. Receiving.\n", pid);
	signal(SIGUSR1, sigone);
	signal(SIGUSR2, sigtwo);
	signal(SIGSTOP, sigstop);
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
	signal(SIGKILL, sigkill);
	while (1)
		wait(stat);
	printf("Stat: %d\n", *stat);
	return (0);
}
