/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:41:03 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 19:57:30 by jahong           ###   ########.fr       */
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
			free_resources(meta, pipes, NULL, g_ws);
	}
	else
	{
		path = ft_strdup(cmd->str[0]);
		if (path == NULL)
		{
			memory_alloc_error();
			free_resources(meta, pipes, NULL, g_ws);
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
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (pipes != NULL && set_file_descriptor(meta, cmd) == -1)
			free_resources(meta, pipes, NULL, 1);
		path = cmd_path_check(meta, cmd, pipes);
		set_pipe_io(meta, cmd, pipes, row);
		if (execve(path, cmd->str, meta->envm) == -1)
		{
			exceve_error_msg(cmd, path);
			free_resources(meta, pipes, path, 127);
		}
	}
	meta->last_pid = pid;
	signal(SIGINT, SIG_IGN);
}
