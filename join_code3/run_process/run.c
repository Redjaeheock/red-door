/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/17 17:54:45 by jahong           ###   ########.fr       */
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
	g_ws = (result >> 8) & 0xFF;
	set_up_signal(meta);
}

void	redirect_with_pipe(t_data *meta, t_cmd_list *cmd, int **pipes, int row)
{
	pid_t	pid;
	int		end;

	meta->pids++;
	pid = fork();
	if (pid == 0)
	{
		end = sndry_arr_len((void **)pipes);
		set_file_descriptor(meta, cmd);
		free_resources(meta, pipes, NULL);
		exit(0);
	}
	else
		meta->last_pid = pid;
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
		else if (cmd->type_cmd == NONE && cmd->type_re != NONE && cmd->type_pipe == PIPE)
			redirect_with_pipe(meta, cmd, pipes, row);
		else if (cmd->type_re != NONE && pipes != NULL && cmd->prev == NULL)
			redirect_with_pipe(meta, cmd, pipes, row);
		if (cmd->type_cmd == NONE && cmd->type_re == NONE && cmd->type_pipe == PIPE)
			row++;
		cmd = cmd->next;
		reset_file_descriptor(meta);
		if (cmd == NULL || cmd->type_pipe == AND || cmd->type_pipe == OR)
			break ;
	}
	return (cmd);
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
	if ((flag != 0 && g_ws != 0) || (flag == 0 && g_ws == 0))
	{
		while (cmd != NULL)
		{
			if (flag == 0 && cmd->type_cmd == NONE && cmd->type_pipe == AND && cmd->type_re == NONE)
				break ;
			else if (flag != 0 && cmd->type_cmd == NONE && cmd->type_pipe == OR && cmd->type_re == NONE)
				break ;
			cmd = cmd->next;
		}
	}
	return (cmd);
}

int	run(t_data *meta, t_cmd_list *cmd)
{
	int	**pipes;
	int	cnt;

	pipes = NULL;
	while (cmd != NULL) // sleep 도중 시그널 적용 시 버그 발생
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
			cmd = check_branch(cmd);
		if (cmd == NULL)
			break ;
		cnt = count_pipe_nodes(meta, cmd);
		if (cnt == -1 || (cnt == 0 && set_file_descriptor(meta, cmd) == -1))
			break ;
		else if (0 < cnt)
			pipes = create_pipes(cnt);
		if (0 < cnt && pipes == NULL)
			break ;
		cmd = execute_cmdline(meta, cmd, pipes);
		pipes = close_pipes(pipes);
		if (0 < meta->pids)
			wait_for_process_reclaim(meta);
		reset_file_descriptor(meta);
	}
	meta->pids = 0;
	return (1);
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
