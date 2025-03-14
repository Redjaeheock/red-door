/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 14:56:40 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "../built_in/built_in.h"

int	connect_in_redirection(t_data *meta, t_cmd_list *cmd)
{
	int	fd; // 리다이렉션 + 파이프 구조 처리 코드 적용 필요

	fd = open(cmd->next->str[0], O_RDONLY);
	if (fd == -1)
	{
		printf("bash: %s: No search file or directory\n", cmd->next->str[0]);
		return (0); // 처리 코드 작성
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
	
	if (cmd->type_re == OUT_REDEC)
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->type_re == GR_REDEC)
		fd = open(cmd->next->str[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("bash: %s: cannot open for system error\n", cmd->next->str[0]);
		return (0);
	}
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
					return (0);
			}
			else
			{
				if (connect_out_redirection(meta, cmd) == 0)
					return (0);
			}
		}
		if (cmd->type_pipe != NONE && cmd->type_cmd != CMD && cmd->type_re == NONE)
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


char	*cmd_path_check(t_data *meta, t_cmd_list *tmp)
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
			return (sndry_alloc_err((void **)pipes)); // 파일 디스크립터 정리
		if (pipe(pipes[row]) == -1)
		{
			pipes[row + 1] = NULL;
			printf("bash: system error use pipe\n");
			return (free_sndry_arr((void **)pipes)); // 파일 디스크립터 정리
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

int	run(t_data *meta)
{
	t_cmd_list	*main;
	int			**pipes;
	char		*path;
	pid_t		pid;
	int			pip_flg;
	int			status;
	int			cnt;
	int			row;
	int			len;

	cnt = 0;
	row = 0;
	main = meta->exec_cmd;
	pipes = NULL;
	while (main != NULL) // sleep 도중 시그널 적용 시 버그 발생
	{
		cnt = 0;
		pip_flg = make_pipes(meta, main, &pipes);
		if (pip_flg == -1)
			return (0);
		while (main != NULL)
		{
			if (main->type_cmd == CMD)
			{
				if (compare_builtin_list(meta, main) == 1)
					pid = builtin(meta, main, pipes, row);
				else
				{
					meta->pids++;
					pid = fork();
					if (pid == 0)
					{
						// signal(SIGINT, (void *)child_process_kill);
						// meta->pids = -1;
						if (pip_flg == 1 && set_file_descriptor(meta, main) == 0)
						{
							free_sndry_arr((void **)pipes);
							exit(0);
						}
						len = sndry_arr_len((void **)pipes);
						set_pipe_io(meta, main, pipes, row);
						if (search_chr_in_str(main->str[0], '/') == 0)
						{
							path = cmd_path_check(meta, main);
							if (path == NULL)
							{
								free_meta_token(meta);
								exit(0);
							}
						}
						else
						{
							path = ft_strdup(main->str[0]);
							if (path == NULL)
							{
								free_meta_token(meta);
								exit(0);
							}
						}
						if (execve(path, main->str, meta->envm) == -1)
						{
							if (access(path, X_OK) != 0)
								printf("bash: %s: No such file or directory\n", path);
							reset_file_descriptor(meta);
							close_pipes(pipes);
							free(path);
							free_meta_token(meta);
							exit(0);
						}
					}
				}
			}
			if (main->type_cmd == NONE && main->type_re == NONE && main->type_pipe == PIPE)
				row++;
			main = main->next;
			if (main == NULL || main->type_pipe == AND || main->type_pipe == OR)
				break ;
		}
		pipes = close_pipes(pipes);
		while (0 < meta->pids)
		{
			wait(&status);
			meta->pids--;
			g_ws = (status >> 8) & 0xFF;
		}
		reset_file_descriptor(meta);
		if (main != NULL)
			main = main->next;
	}
	meta->pids = 0;
	printf("exit_no = [%d]\n", g_ws);
	return (0);
}

int	rutin_free(t_data *meta, char *str)
{
	if (meta->exec_cmd)
	{
		//printf_exec_commads(meta->exec_cmd);
		free_exec_linked_list(meta->exec_cmd);
		meta->exec_cmd = NULL;
	}
	meta->tokens = free_t_list(meta->tokens);
	add_history_and_free(&str);
	return (0);
}
