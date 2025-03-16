/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/08 16:26:00 by jahong           ###   ########.fr       */
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
		return (0);
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
	static t_cmd_list	*keep;
	int					flag;

	flag = 0;
	if (keep == NULL || keep == cmd)
	{
		flag = 1;
		if (keep == NULL)
			keep = cmd;
		else
			cmd = cmd->next;
	}
	while (flag == 1 && keep != NULL)
	{
		if (keep->type_re != NONE)
		{

			if (keep->type_re == IN_REDEC || keep->type_re == HEREDOC)
			{
				if (connect_in_redirection(meta, keep) == 0)
					return (0);
			}
			else
			{
				if (connect_out_redirection(meta, keep) == 0)
					return (0);
			}
		}
		if (keep->type_pipe != NONE)
			return (1);
		keep = keep->next;
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

int	**make_pipes(t_data *meta, t_cmd_list *cmd)
{
	int	**pipes;
	int	cnt;

	cnt = 0;
	while (cmd != NULL)
	{
		if (cmd->type_pipe == AND || cmd->type_pipe == OR)
			break ;
		if (cmd->str == NULL && cmd->type_re == NONE && cmd->type_pipe == PIPE)
			cnt++;
		cmd = cmd->next;
	}
	pipes = create_pipes(cnt);
	return (pipes);
}

int	run(t_data *meta)
{
	t_cmd_list	*main;
	int			**pipes;
	char		*path;
	pid_t		pid;
	int			status;
	int			cnt;
	int			row;
	int			len;

	cnt = 0;
	row = 0;
	main = meta->exec_cmd;
	pipes = NULL;
	// printf("run program\n");
	while (main != NULL) // sleep 도중 시그널 적용 시 버그 발생
	{
		pipes = make_pipes(meta, main);
		if (pipes == NULL)
			return (0);
		if (pipes[0] == NULL)
		{
			free(pipes);
			pipes = NULL;
		}
		while (main != NULL)
		{
			if (set_file_descriptor(meta, main) == 0)
				return ((free_sndry_arr((void **)pipes), 0));
			if (main->type_cmd == CMD)
			{
				if (main->type_pipe == NONE)
				{
					if (main->prev != NULL && main->prev->type_pipe == PIPE)
						main->prev->type_pipe = main->prev->type_pipe;
					else
					{
						if (change_dollar_underbar(meta, main) != 1)
							return ((free_sndry_arr((void **)pipes), 0)); // fd 정리 필요
					}
				}
				if (compare_builtin_list(meta, main) == 1)
					pid = builtin(meta, main);
				else
				{
					meta->pids++;
					pid = fork();
					if (pid == 0)
					{
						// signal(SIGINT, (void *)child_process_kill);
						// meta->pids = -1;
						len = sndry_arr_len((void **)pipes);
						
						// if (main->prev != NULL && main->prev->type_pipe == PIPE)
						// {
						// 	set_pipe_in(meta, pipes, &row);
						// }
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
							free(path);
							free_meta_token(meta);
							exit(0);
						}
					}
				}
			}
			main = main->next;
			if (main == NULL || main->type_pipe == AND || main->type_pipe == OR)
				break ;
		}
		while (0 < meta->pids)
		{
			//printf("wait %d\n", meta->pids);
			wait(&status);
			meta->pids--;
		}
		reset_file_descriptor(meta);
		if (main != NULL)
			main = main->next;
	}
	g_ws = status;
	row = 0;
	while (pipes != NULL && pipes[row] != NULL)
	{
		close(pipes[row][0]);
		close(pipes[row][1]);
		free(pipes[row]);
		row++;
	}
	free(pipes);
	meta->pids = 0;
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
