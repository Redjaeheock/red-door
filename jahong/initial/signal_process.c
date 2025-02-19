/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:23:52 by jahong            #+#    #+#             */
/*   Updated: 2025/02/19 20:15:08 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(int signum, sigset_t *preset)
{
	sigset_t tmp;

	sigemptyset(&tmp);
	// sigaddset(&tmp, SIGINT);
	sigprocmask(SIG_UNBLOCK, &tmp, preset);
}

void	handle_rollback(int signum, sigset_t *preset)
{
	sigprocmask(SIG_SETMASK, preset, NULL);
}

void	set_up_signal(void)
{
	struct sigaction sig;

	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
