/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:55:20 by dabae             #+#    #+#             */
/*   Updated: 2024/06/28 11:40:05 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Save exit status in global variable depending on exit status of the process */
void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		g_exit_status = 130;
	else
		g_exit_status = 126;
}

void	handle_signal_during_execution(int sig)
{
	if (sig == SIGQUIT)
		ft_error("Quit", 131);
	else
	{
		g_exit_status = 130;
		printf("\n");
	}
	rl_redisplay();
}

void	setup_parent_signals(void)
{
	signal(SIGINT, handle_signal_before);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal_before(int sig)
{
	(void)sig;
	printf("\n");
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("^C\n");
	exit(130);
}
