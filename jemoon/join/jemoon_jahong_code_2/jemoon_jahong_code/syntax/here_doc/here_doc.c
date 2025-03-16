/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:31 by jahong            #+#    #+#             */
/*   Updated: 2025/02/19 20:58:49 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define BASE_PATH "/tmp/"
#define UNSIGNED_INT_MAX 4294967295

static int	*g_stop_loop = NULL;

void	restore_signal_handler(struct sigaction *old_sa)
{
	sigaction(SIGINT, old_sa, NULL);
}

void	ctrl_c_handler(int signum)
{
	char	*path;
	int		fd;

	close(STDIN_FILENO);
	path = ttyname(STDOUT_FILENO);
	fd = open(path, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	set_heredoc_signal(struct sigaction *origin, int *loop)
{
	struct sigaction	tmp;

	g_stop_loop = loop;
	tmp.sa_handler = ctrl_c_handler;
	tmp.sa_flags = 0;
	sigemptyset(&tmp.sa_mask);
	sigaction(SIGINT, &tmp, origin);
}

char	**alloc_f_list(char *filename)
{
	char	**f_list;

	f_list = (char **)malloc(sizeof(char *) * 2);
	if (f_list == NULL)
		return (NULL);
	f_list[0] = ft_strdup(filename);
	if (f_list[0] == NULL)
		return (sndry_alloc_err((void **)f_list));
	f_list[1] = NULL;
	return (f_list);
}

char	**make_f_list(char *eof, char *filename)
{
	struct sigaction	preset;
	sigset_t			origin;
	char				*content;
	int					fd;
	int					loop;

	loop = 1;
	fd = open(filename, O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("fd = -1\n");
		return ((free(filename), NULL));
	}
	// set_heredoc_signal(&preset, &loop);
	// handle_heredoc(0, &origin);
	while (loop)
	{
		content = readline("> ");
		if (content == NULL)
			return ((close(fd), NULL));
		if (ft_strcmp(content, eof) == 0)
		{
			free(content);
			break ;
		}
		ft_putstr_fd(content, fd);
		ft_putstr_fd("\n", fd);
		free(content);
	}
	// handle_rollback(0, &origin);
	close(fd);
	return (alloc_f_list(filename));
}

char	*make_filename(unsigned int n)
{
	int		fd;
	char	*num;
	char	*filename;
	// printf("make filename\n");
	n = (int)n;
	num = ft_itoa(n);
	if (num == NULL)
		return (NULL);
	filename = ft_strjoin_v2(BASE_PATH, num);
	free(num);
	if (filename == NULL)
		return (NULL);
	// printf("creat filename = %s\n", filename);
	fd = open(filename, O_RDWR | O_APPEND | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return ((free(filename), NULL));
	close(fd);
	return (filename);
}

int	here_doc(t_list	*tokens)
{
	char			**file_list;
	char			*filename;
	unsigned int	cnt;

	cnt = 0;
	while (1)
	{
		filename = make_filename(cnt);
		if (filename != NULL)
			break ;
		if (cnt == UNSIGNED_INT_MAX && filename == NULL)
			return (0);
		cnt++;
	}
	file_list = make_f_list(tokens->token, filename);
	free(filename);
	if (file_list == NULL)
		return (0);
	tokens->f_list = file_list;
	printf("filename is %s\n", tokens->f_list[0]);
	return (1);
}
