/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:41:03 by jahong            #+#    #+#             */
/*   Updated: 2025/03/17 17:54:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_check_into_env(t_data *meta, t_cmd_list *tmp)
{
	char	*path;
	int		row;

	row = 0;
	if (meta->path == NULL && access(tmp->str[0], X_OK) == -1)
		return ((perror(tmp->str[0]), NULL));
	while (meta->path[row] != NULL)
	{
		path = ft_strjoin_v2(meta->path[row], tmp->str[0]);
		if (path == NULL)
			return (memory_alloc_error());
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		row++;
	}
	reset_file_descriptor(meta);
	meta->oldstderr = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: command not found\n", tmp->str[0]);
	g_ws = 127;
	return (NULL);
}

char	*cmd_path_check(t_data *meta, t_cmd_list *cmd, int **pipes)
{
	char	*path;

	if (search_chr_in_str(cmd->str[0], '/') == 0)
	{
		path = path_check_into_env(meta, cmd);
		if (path == NULL)
		{
			free_resources(meta, pipes, NULL);
			exit(g_ws);
		}
	}
	else
	{
		path = ft_strdup(cmd->str[0]);
		if (path == NULL)
		{
			memory_alloc_error();
			free_resources(meta, pipes, NULL);
			exit(g_ws);
		}
	}
	return (path);
}

void	external(t_data *meta, t_cmd_list *cmd, int **pipes, int row)
{
	char	*path;
	pid_t	pid;

	meta->pids++;
	pid = fork();
	if (pid == 0)
	{
		set_up_signal_child_process(meta);
		if (pipes != NULL && set_file_descriptor(meta, cmd) == 0)
		{
			free_resources(meta, pipes, NULL);
			exit(0);
		}
		path = cmd_path_check(meta, cmd, pipes);
		set_pipe_io(meta, cmd, pipes, row);
		if (execve(path, cmd->str, meta->envm) == -1)
		{
			if (access(path, X_OK) != 0)
				perror(path);
			free_resources(meta, pipes, path);
			exit(127);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		meta->last_pid = pid;
	}
}
