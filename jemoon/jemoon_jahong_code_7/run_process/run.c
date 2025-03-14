/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 13:46:21 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "../built_in/built_in.h"

void	wait_for_process_reclaim(t_data *meta)
{
	int	status;

	while (0 < meta->pids)
	{
		wait(&status);
		meta->pids--;
	}
}
t_cmd_list *execute_cmdline(t_data *meta, t_cmd_list *cmd, int **pipes)
{
	char	*path;
	int		row;

	row = 0;
	while (cmd != NULL)
	{
		if (cmd->type_cmd == CMD)
		{
			if (compare_builtin_list(meta, cmd) == 1)
				builtin(meta, cmd, pipes, row);
			else
				external(meta, cmd, pipes, row);
		}
		if (cmd->type_cmd == NONE && cmd->type_re == NONE && cmd->type_pipe == PIPE)
			row++;
		cmd = cmd->next;
		if (cmd == NULL || cmd->type_pipe == AND || cmd->type_pipe == OR)
			break ;
	}
	return (cmd);
}
int	run(t_data *meta)
{
	t_cmd_list	*cmd;
	int			**pipes;

	cmd = meta->exec_cmd;
	pipes = NULL;
	while (cmd != NULL) // sleep 도중 시그널 적용 시 버그 발생
	{
		if (make_pipes(meta, cmd, &pipes) == -1)
			return (0);
		cmd = execute_cmdline(meta, cmd, pipes);
		pipes = close_pipes(pipes);
		wait_for_process_reclaim(meta);
		reset_file_descriptor(meta);
	}
	meta->pids = 0;
	return (0);
}

int	rutin_free(t_data *meta, char *str)
{
	if (meta->exec_cmd)
	{
		//printf_exec_commads(meta->exec_cmd);
		free_exec_linked_list(meta->exec_cmd);
		meta->exec_cmd = NULL;
	}
	meta->tokens = free_t_list(meta->tokens);
	add_history_and_free(&str);
	return (0);
}
