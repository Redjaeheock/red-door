/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:23:52 by jahong            #+#    #+#             */
/*   Updated: 2025/03/17 20:31:15 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flag_check(int signum, siginfo_t *tmp, void *info)
{
	static t_data	*meta;

	(void)tmp;
	//write(0, tmp, 0);
	if (meta == NULL)
	{
		meta = (t_data *)info;
		return ;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		if (meta->heredoc != 1)
			rl_redisplay();
		else
		{
			close(STDIN_FILENO);
			meta->stdin_flag = -1;
		}
	}
}

void	child_process_signal_handler(int signum, siginfo_t *tmp, void *info)
{
	g_ws = 130;
	exit(g_ws);
}

void	newline(int signum, siginfo_t *tmp, void *info)
{
	rl_on_new_line();
	//printf("\n");
	// rl_replace_line("", 1);
	printf("\n");
	rl_redisplay();
}

void	set_up_signal(t_data *meta, int flag)
{
	struct sigaction	sig;
	struct sigaction	tmp;
	static int			init;

	if (init == 0)
	{
		flag_check(0, NULL, meta);
		init = 1;
	}
	if (flag == 0)
	{
		sigemptyset(&sig.sa_mask);
		sig.sa_flags = SA_SIGINFO;
		sig.sa_sigaction = flag_check;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else
	{
		sigemptyset(&tmp.sa_mask);
		tmp.sa_flags = SA_SIGINFO;
		tmp.sa_sigaction = newline;
		sigaction(SIGINT, &tmp, NULL);
		flag = 1;
	}
}

void	set_up_signal_child_process(t_data	*meta)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = child_process_signal_handler;
	sigaction(SIGINT, &sig, NULL);
}
