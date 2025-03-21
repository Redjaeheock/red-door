/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:26:05 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 21:09:39 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"

void	*close_pipes(int **pipes)
{
	int	row;

	row = 0;
	if (pipes == NULL)
		return (NULL);
	while (pipes[row] != NULL)
	{
		close(pipes[row][0]);
		close(pipes[row][1]);
		free(pipes[row]);
		row++;
	}
	free(pipes);
	return (NULL);
}

int	**create_pipes(int len)
{
	int	**pipes;
	int	row;

	pipes = (int **)malloc(sizeof(int *) * (len + 1));
	if (pipes == NULL)
		return (memory_alloc_error());
	row = 0;
	while (row < len)
	{
		pipes[row] = (int *)malloc(sizeof(int) * 2);
		if (pipes[row] == NULL)
		{
			close_pipes(pipes);
			return (memory_alloc_error());
		}
		if (pipe(pipes[row]) == -1)
		{
			pipes[row + 1] = NULL;
			perror("pipe");
			return (close_pipes(pipes));
		}
		row++;
	}
	pipes[row] = NULL;
	return (pipes);
}

int	count_pipe_nodes(t_data *meta, t_cmd_list *cmd)
{
	t_cmd_list	*tmp;
	int			cnt;

	cnt = 0;
	tmp = cmd;
	if (cmd->type_pipe == AND || cmd->type_pipe == OR)
		cmd = cmd->next;
	while (cmd != NULL)
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
		{
			if (cnt == 0 && change_dollar_underbar(meta, cmd->prev) != 1)
				return (-1);
			break ;
		}
		if (check_pipe_branch(cmd) == 1)
			cnt++;
		if (cnt == 0 && cmd->next == NULL)
		{
			if (change_dollar_underbar(meta, cmd) != 1)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (cnt);
}

void	set_pipe_io(t_data *meta, t_cmd_list *cmd, int **pipes, int row)
{
	int	cnt;
	int	end;

	cnt = 0;
	end = sndry_arr_len((void **)pipes);
	while (cnt < end)
	{
		if (cnt != row -1)
			close(pipes[cnt][0]);
		if (cnt != row)
			close(pipes[cnt][1]);
		cnt++;
	}
	if (0 < row)
	{
		if (cmd->type_cmd == CMD && meta->oldstdin == -1)
			dup2(pipes[row - 1][0], STDIN_FILENO);
		close(pipes[row - 1][0]);
	}
	if (row < end)
	{
		if (cmd->type_cmd == CMD && meta->oldstdout == -1)
			dup2(pipes[row][1], STDOUT_FILENO);
		close(pipes[row][1]);
	}
}
