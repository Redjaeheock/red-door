/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/15 14:11:24 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

void	execute_builtin(t_data *meta, t_cmd_list *exec_cmd)
{
	if (ft_strcmp(exec_cmd->str[0], "exit") == 0)
		minishell_exit(meta, exec_cmd);
	if (ft_strcmp(exec_cmd->str[0], "echo") == 0)
		minishell_echo(meta, exec_cmd);
	if (ft_strcmp(exec_cmd->str[0], "pwd") == 0)
		minishell_pwd(meta);
	if (ft_strcmp(exec_cmd->str[0], "env") == 0)
		minishell_env(meta, exec_cmd);
	if (ft_strcmp(exec_cmd->str[0], "export") == 0)
		minishell_export(meta, exec_cmd);
	if (ft_strcmp(exec_cmd->str[0], "unset") == 0)
		minishell_unset(meta, exec_cmd);
	if (ft_strcmp(exec_cmd->str[0], "cd") == 0)
		minishell_cd(meta, exec_cmd);
}

void	builtin(t_data *meta, t_cmd_list *exec_cmd, int **pipes, int row)
{
	pid_t	pid;

	pid = 0;
	if (pipes != NULL)
	{
		meta->pids++;
		pid = fork();
	}
	if (pid == 0)
	{
		if (pipes != NULL && set_file_descriptor(meta, exec_cmd) == 0)
		{
			close_pipes(pipes);
			exit(0);
		}
		set_pipe_io(meta, exec_cmd, pipes, row);
		execute_builtin(meta, exec_cmd);
		if (pipes != NULL)
		{
			free_resources(meta, pipes, NULL);
			exit(0);
		}
	}
	else
		meta->last_pid = pid;
}

int	compare_builtin_list(t_data *meta, t_cmd_list *exec_cmd)
{
	if (ft_strcmp(exec_cmd->str[0], "exit") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "echo") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "env") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "export") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "unset") == 0)
		return (1);
	if (ft_strcmp(exec_cmd->str[0], "cd") == 0)
		return (1);
	return (0);
}
