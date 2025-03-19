/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:07:01 by jahong            #+#    #+#             */
/*   Updated: 2025/03/19 17:28:47 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"

int	redirect_with_pipe(t_data *meta, t_cmd_list *cmd, int **pipes)
{
	pid_t	pid;

	meta->pids++;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		set_file_descriptor(meta, cmd);
		free_resources(meta, pipes, NULL, 0);
	}
	meta->last_pid = pid;
	return (1);
}

int	check_pipe_except_case(t_data *meta, t_cmd_list *cmd, int **pipes)
{
	if (check_redi_with_pipe(cmd) == 1)
	{
		if (redirect_with_pipe(meta, cmd, pipes) != 1)
		 	return (-1);
		return (1);
	}
	else if (cmd->type_re != NONE && pipes != NULL && cmd->prev == NULL)
	{
		if (redirect_with_pipe(meta, cmd, pipes) != 1)
			return (-1);
		return (1);
	}
	return (0);
}

t_cmd_list	*check_branch(t_cmd_list *cmd)
{
	int	flag;

	flag = 0;
	if (cmd->type_pipe == AND)
		flag = 1;
	else if (cmd->type_pipe == OR)
		flag = 0;
	cmd = cmd->next;
	if (g_ws == 130)
		while (cmd != NULL)
			cmd = cmd->next;	
	if ((flag != 0 && g_ws != 0) || (flag == 0 && g_ws == 0))
	{
		while (cmd != NULL)
		{
			if (flag == 0 && check_and_branch(cmd) == 1)
				break ;
			else if (flag != 0 && check_or_branch(cmd) == 1)
					break ;
			cmd = cmd->next;
		}
	}
	return (cmd);
}
