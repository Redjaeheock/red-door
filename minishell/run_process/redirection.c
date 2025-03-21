/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:42:17 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 21:55:42 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"

void	verify_open_failure(char *str)
{
	// 경우에 따라 에러 문구 처리하기기
	g_ws = 1;
	if (search_chr_in_str(str, '$') == 1)
	{
		printf("bash: %s: ambiguous redirect\n", str);
		return ;
	}
	printf("bash: %s: No such file or directory\n", str);
}

int	connect_in_redirection(t_data *meta, t_cmd_list *cmd)
{
	int	fd;

	fd = open(cmd->next->str[0], O_RDONLY);
	if (fd == -1)
	{
		verify_open_failure(cmd->next->str[0]);
		return (0);
	}
	if (meta->oldstdin == -1)
		meta->oldstdin = dup(STDIN_FILENO);
	else
		dup2(meta->oldstdin, STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	connect_out_redirection(t_data *meta, t_cmd_list *cmd)
{
	int	fd;

	if (search_chr_in_str(cmd->next->str[0], '$') == 1)
		return ((verify_open_failure(cmd->next->str[0]), 0));
	if (cmd->type_re == OUT_REDEC)
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->type_re == GR_REDEC)
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ((verify_open_failure(cmd->next->str[0]), 0));
	if (meta->oldstdout == -1)
		meta->oldstdout = dup(STDOUT_FILENO);
	else
		dup2(meta->oldstdout, STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	set_file_descriptor(t_data *meta, t_cmd_list *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->type_re != NONE)
		{
			if (cmd->type_re == IN_REDEC || cmd->type_re == HEREDOC)
			{
				if (connect_in_redirection(meta, cmd) == 0)
					return (-1);
			}
			else
			{
				if (connect_out_redirection(meta, cmd) == 0)
					return (-1);
			}
		}
		if (is_cmd_branch(cmd) == 1)
			break ;
		cmd = cmd->next;
	}
	return (1);
}

void	reset_file_descriptor(t_data *meta)
{
	if (meta->oldstdin != -1)
	{
		dup2(meta->oldstdin, STDIN_FILENO);
		close(meta->oldstdin);
		meta->oldstdin = -1;
	}
	if (meta->oldstdout != -1)
	{
		dup2(meta->oldstdout, STDOUT_FILENO);
		close(meta->oldstdout);
		meta->oldstdout = -1;
	}
	if (meta->oldstderr != -1)
	{
		dup2(meta->oldstderr, STDERR_FILENO);
		close(meta->oldstderr);
		meta->oldstderr = -1;
	}
}
