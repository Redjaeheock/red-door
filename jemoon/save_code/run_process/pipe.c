/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:26:05 by jahong            #+#    #+#             */
/*   Updated: 2025/03/15 09:12:11 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (memory_alloc_error()); // 파일 디스크립터 정리
		}
		if (pipe(pipes[row]) == -1)
		{
			pipes[row + 1] = NULL;
			printf("system error using pipe\n");
			return (close_pipes(pipes)); // 파일 디스크립터 정리
		}
		row++;
	}
	pipes[row] = NULL;
	return (pipes);
}

int	make_pipes(t_data *meta, t_cmd_list *cmd, int ***pipes)
{
	t_cmd_list	*tmp;
	int			cnt;

	cnt = 0;
	tmp = cmd;
	while (cmd != NULL)
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
		{
			if (cnt == 0 && change_dollar_underbar(meta, cmd) != 1)
				return (-1);
			break ;
		}
		if (cmd->type_cmd == NONE && cmd->type_re == NONE && cmd->type_pipe == PIPE)
			cnt++;
		cmd = cmd->next;
	}
	if (cnt == 0)
		return (set_file_descriptor(meta, tmp));
	*pipes = create_pipes(cnt);
	if (*pipes == NULL)
		return (-1);
	return (1);
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
		if (cmd->type_cmd == CMD && meta->oldstdout == -1 && meta->oldstdin == -1)
			dup2(pipes[row][1], STDOUT_FILENO);
		close(pipes[row][1]);
	}
}
