/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 14:02:41 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "../built_in/built_in.h"

void	set_fd(t_cmd_list *cmd)
{
	int	fd;

	if (cmd->type_re == IN_REDEC || cmd->type_re == HEREDOC)
	{
		fd = open(cmd->next->str[0], O_RDONLY);
		if (fd == -1)
			return ; // 처리 코드 작성W
		dup2(fd, 0);
		close(fd);
	}
	else if (cmd->type_re == OUT_REDEC)
	{
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return ;
		dup2(fd, 1);
		// close(fd);
	}
	else if (cmd->type_re == GR_REDEC)
	{
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return ;
		dup2(fd, 1);
		// close(fd);
	}
}

int	run(t_data *meta)
{
	t_cmd_list	*temp;
	pid_t		pid;
	int			status;

	printf("run set fd\n");
	temp = meta->exec_cmd;
	while (temp != NULL)
	{
		if (temp->type_re != NONE && temp->str != NULL)
			set_fd(temp);
		temp = temp->next;
	}

	temp = meta->exec_cmd;
	printf("run program\n");
	while (temp != NULL)
	{
		if (temp->str != NULL)
		{
			if (temp->type_pipe == NONE)
			{
				if (temp->prev != NULL && temp->prev->type_pipe != NONE)
					temp->prev->type_pipe = temp->prev->type_pipe;
				else
				{
					if (change_dollar_underbar(meta, temp) != 1)
						return (0);
				}
			}
			if (compare_builtin_list(meta, temp) == 1)
				pid = builtin(meta, temp);
			if (compare_builtin_list(meta, temp) != 1)
			{
				printf("temp str[0] = %s\n", temp->str[0]);
				meta->pids++;
				pid = fork();
				if (pid == 0)
				{
					// if (path_check(temp) == 0)
					// {
					// 	free_meta_token(meta);
					// 	exit(0);
					// }
					// else 
						if (execve("/usr/bin/ls", temp->str, meta->envm) == -1)
						{
							free_meta_token(meta);
							exit(127);
						}
				}
			}
			if (pid > 0)
			{
				wait(&status);
				g_ws = (status >> 8) & 0xFF;
			}
		}
		temp = temp->next;
	}
	printf("exit_no = [%d] \n", g_ws);
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
