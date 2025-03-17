/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:32:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/14 15:35:01 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

pid_t	builtin(t_data *meta, t_cmd_list *exec_cmd, int **pipes, int row)
{
	pid_t	pid;
	int		status;
	int		flag;

	pid = 0;
	flag = 0;
	if (pipes != NULL)
		flag = 1;
	if (flag == 1)
	{
		meta->pids++;
		pid = fork();
	}
	if (pid == 0)
	{
		// 글로벌 exit 번호로 에러 구분시키기
		if (flag == 1 && set_file_descriptor(meta, exec_cmd) == 0)
		{
			free_sndry_arr((void **)pipes);
			exit(0);
		}

		set_pipe_io(meta, exec_cmd, pipes, row);
		if (ft_strcmp(exec_cmd->str[0], "exit") == 0)
			minishell_exit(meta, exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "echo") == 0)
			minishell_echo(exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "pwd") == 0)
			minishell_pwd(meta, exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "env") == 0)
			minishell_env(meta, exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "export") == 0)
			minishell_export(meta, exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "unset") == 0)
			minishell_unset(meta, exec_cmd);
		if (ft_strcmp(exec_cmd->str[0], "cd") == 0)
			minishell_cd(meta, exec_cmd);
		if (flag == 1)
		{
			free_sndry_arr((void **)pipes);
			free_meta_token(meta);
			exit(g_ws);
		}
	}
	return (pid);
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

int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-')
		return (1);
	return (0);
}
