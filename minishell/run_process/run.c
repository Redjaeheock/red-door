/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/22 21:05:51 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../built_in/built_in.h"
#include "../syntax/syntax.h"

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


int substitute(t_data *meta, t_cmd_list *cmd, int row, char c)
{
	t_tmp	*node;
	char	**tmp;
	int		*keep;
	int		var;

	if (search_chr_in_str(cmd->str[row], '$') == 0)
		return (2);
	var = measure_length_quote_set(cmd->str[row], var = 0, c);
	tmp = dividing_sub_token(cmd->str[row], var);
	if (tmp == NULL)
		return (0);
	node = do_substitute_dollar_sign(meta, tmp, c);
	free_sndry_arr((void **)tmp);
	if (node == NULL)
		return (0);
	var = join_sub_tokens(cmd, node, c, row);
	free_t_tmp(node);
	if (var == 0)
		return (0);
	return (1);

}

char	**remake_cmd_len(t_cmd_list *cmd)
{
	char	**tmp;
	int	row;
	int	cnt;

	row = 0;
	cnt = 0;
	while (cmd->str[row] != NULL)
	{
		cnt ++;
		if (ft_strcmp(cmd->str[row], "") == 0)
		{
			if (search_chr_in_str(cmd->f_list[row], '$') == 1)
			   cnt--;
		}
		row++;
	}
	tmp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (tmp == NULL)
		return (memory_alloc_error());
	return (tmp);
}

int	remake_cmd_str(t_cmd_list *cmd)
{
	char	**tmp;
	int		row1;
	int		row2;

	row1 = 0;
	row2 = 0;
	tmp = remake_cmd_len(cmd);
	if (tmp == NULL)
		return (0);
	while (cmd->str[row1] != NULL)
	{
		if (cmd->str[row1][0] == '\0')
		{
			if (search_chr_in_str(cmd->f_list[row1], '$') == 1)
			{
				row1++;
				continue ;
			}
		}
		else
		{
			tmp[row2] = strdup(cmd->str[row1]);
			if (tmp[row2] == NULL)
				return (0);
		}
		row1++;
		row2++;
	}
	tmp[row2] = NULL;
	free_sndry_arr((void **)cmd->str);
	cmd->str = tmp;
	return (1);
}

int	substitute_cmd(t_data *meta, t_cmd_list *cmd, char c)
{
	char	result;
	int		row;
	int		len;

	if (is_cmd_branch(cmd) == 1 || check_redi(cmd) == 1)
		return (1);
	len = sndry_arr_len((void **)cmd->str);
	cmd->f_list = (char **)malloc(sizeof(char *) * (len + 1));
	if (cmd->f_list == NULL)
		return (0);
	row = 0;
	while (cmd->str[row] != NULL)
	{
		result = substitute(meta, cmd, row, 'c');
		if (result == 0)
			return (result);
		if (result == 2)
		{
			cmd->f_list[row] = ft_strdup(cmd->str[row]);
			if (cmd->f_list[row] == NULL)
				return (0);
		}
		row++;
	}
	cmd->f_list[row] = NULL;
	if (remake_cmd_str(cmd) == 0)
		return (0);
	return (1);
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

	pipes = NULL;
	while (cmd != NULL)
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
			cmd = check_branch(cmd);
		if (cmd == NULL)
			break ;
		if (substitute_cmd(meta, cmd, 'h') == 0)
			break;
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
