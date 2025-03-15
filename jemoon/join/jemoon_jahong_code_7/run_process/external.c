/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:41:03 by jahong            #+#    #+#             */
/*   Updated: 2025/03/15 13:43:12 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_check_into_env(t_data *meta, t_cmd_list *tmp)
{
	char	*path;
	int		row;

	row = 0;
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
	printf("%s: command not found\n", tmp->str[0]);
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
			exit(127);
		}
	}
	else
	{
		path = ft_strdup(cmd->str[0]);
		if (path == NULL)
		{
			memory_alloc_error();
			free_resources(meta, pipes, NULL);
			exit(127);
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
		// signal(SIGINT, (void *)child_process_kill);
		// meta->pids = -1;
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
				printf("bash: %s: No such file or directory\n", path);
			free_resources(meta, pipes, path);
			exit(127);
		}
	}
	else
		meta->last_pid = pid;
}
