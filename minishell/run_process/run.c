/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 21:15:49 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../built_in/built_in.h"

void	after_run_son_process(int result, int sig)
{
	if ((result & 0x7F) == 0)
	{
		g_ws = (result >> 8) & 0xFF;
		if (sig + 128 == 130)
			printf("\n");
		return ;
	}
	else
		g_ws = 128 + (result & 0x7F);
	if (g_ws == 131)
		printf("Quit (core dumped)\n");
	else if (g_ws == 130 || g_ws == 131)
		printf("\n");
}

void	wait_for_process_reclaim(t_data *meta)
{
	pid_t	pid;
	int		status;
	int		result;
	int		sig;

	result = 0;
	sig = 0;
	while (0 < meta->pids)
	{
		pid = wait3(&status, 0, NULL);
		if ((status & 0x7F) != 0 && sig == 0)
			sig = (status & 0x7F);
		if (pid == meta->last_pid)
			result = status;
		meta->pids--;
	}
	set_up_signal(meta);
	after_run_son_process(result, sig);
}

t_cmd_list	*execute_cmdline(t_data *meta, t_cmd_list *cmd, int **pipes)
{
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
		else if (check_pipe_except_case(meta, cmd, pipes) == -1)
			redirect_with_pipe(meta, cmd, pipes);
		if (check_pipe_branch(cmd) == 1)
			row++;
		cmd = cmd->next;
		reset_file_descriptor(meta);
		if (cmd == NULL || cmd->type_pipe == AND || cmd->type_pipe == OR)
			break ;
	}
	return (cmd);
}

int	set_fd_n_pipe_io(t_data *meta, t_cmd_list **cmd, int ***pipes)
{
	int	cnt;

	cnt = count_pipe_nodes(meta, *cmd);
	if (cnt == -1)
		return (-1);
	if (cnt == 0 && set_file_descriptor(meta, *cmd) == -1)
	{
		while ((*cmd)->next != NULL)
		{
			*cmd = (*cmd)->next;
			if ((*cmd)->type_pipe == AND || (*cmd)->type_pipe == OR)
				break ;
		}
		return (0);
	}
	else if (0 < cnt)
		*pipes = create_pipes(cnt);
	if (0 < cnt && *pipes == NULL)
		return ((reset_file_descriptor(meta), -1));
	return (1);
}

int	run(t_data *meta, t_cmd_list *cmd)
{
	int	**pipes;
	int	result;
	int	cnt;

	pipes = NULL;
	while (cmd != NULL)
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
			cmd = check_branch(cmd);
		if (cmd == NULL)
			break ;
		result = set_fd_n_pipe_io(meta, &cmd, &pipes);
		if (result == -1)
			break ;
		if (result == 0)
			continue ;
		cmd = execute_cmdline(meta, cmd, pipes);
		pipes = close_pipes(pipes);
		if (0 < meta->pids)
			wait_for_process_reclaim(meta);
		reset_file_descriptor(meta);
	}
	meta->pids = 0;
	return (1);
}
