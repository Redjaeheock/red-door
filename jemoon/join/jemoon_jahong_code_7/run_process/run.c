/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/15 19:48:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "../built_in/built_in.h"

void	wait_for_process_reclaim(t_data *meta)
{
	pid_t	pid;
	int		status;
	int		result;

	pid = 0;
	while (0 < meta->pids)
	{
		pid = wait3(&status, 0, NULL);
		if (pid == meta->last_pid)
			result = status;
		meta->pids--;
	}
	g_ws =  (result >> 8) & 0xFF;
}
/*
void	wait_for_process_reclaim(t_data *meta)
{
	int	*status;
	int	row;

	row = 0;
	status = (int *)malloc(sizeof(int) * (meta->pids));
	if (status == NULL)
		return ;
	while (row < meta->pids)
	{
		wait(status + row);
		printf("Child process %d finished, status: %d\n", row + 1, (*(status + row) >> 8) & 0xFF);
		row++;
	}
	g_ws = (*(status) >> 8) & 0xFF;
	printf("check_gwd [%d]\n", g_ws);
	free(status);
	meta->pids = 0;
}
*/

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
		if (cmd->type_cmd == NONE && cmd->type_pipe == AND && cmd->type_re == NONE)
		{
			cmd = cmd->next;
			if (g_ws != 0)
			{
				while (cmd != NULL)
				{
					if (cmd->type_cmd == NONE && cmd->type_pipe != NONE && cmd->type_re == NONE)
						break ;
					cmd = cmd->next;
				}
			}
			if (cmd == NULL)
				return (0);
		}
		if (make_pipes(meta, cmd, &pipes) == -1)
			return (0);
		cmd = execute_cmdline(meta, cmd, pipes);
		pipes = close_pipes(pipes);
		if (0 < meta->pids)
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
		printf_exec_commads(meta->exec_cmd);
		free_exec_linked_list(meta->exec_cmd);
		meta->exec_cmd = NULL;
	}
	meta->tokens = free_t_list(meta->tokens);
	add_history_and_free(&str);
	return (0);
}
