/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:23:52 by jahong            #+#    #+#             */
/*   Updated: 2025/03/18 23:14:24 by jahong           ###   ########.fr       */
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
		rl_replace_line("", 1);
		rl_on_new_line();
		printf("\n");
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
	static t_data	*meta;

	if (meta == NULL)
	{
		meta = (t_data *)info;
		return ;
	}
	else
		printf("Quit (core dumped)\n");
}

void	set_up_signal(t_data *meta)
{
	struct sigaction	sig;
	static int			init;

	if (init == 0)
	{
		flag_check(0, NULL, meta);
		init = 1;
	}
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = flag_check;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sig, NULL);
}

void	set_up_signal_child_process(t_data	*meta)
{
	struct sigaction	sig;
	static int			init;


	// sigemptyset(&sig.sa_mask);
	// sig.sa_flags = SA_SIGINFO;
	// sig.sa_sigaction = NULL;
	signal(SIGQUIT, SIG_DFL);
	// sigaction(SIGQUIT, &sig, NULL);
}
