/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:31 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 22:12:39 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BASE_PATH "/tmp/"
#define UNSIGNED_INT_MAX 4294967295

void	reset_stdin_fileno(t_data *meta)
{
	char	*path;
	int		fd;

	path = ttyname(STDOUT_FILENO);
	fd = open(path, O_RDONLY); // fd == -1 코드 작성성
	dup2(fd, STDIN_FILENO);
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

int	make_f_list(char *eof, char *filename)
{
	char	*content;
	int		fd;

	if (ft_strcmp(eof, "\"\"") == 0 || ft_strcmp(eof, "\'\'") == 0)
		eof = "";
	fd = open(filename, O_RDWR, 0644);
	if (fd == -1)
		return (0);
	while (1)
	{
		content = readline("> ");
		if (content == NULL)
			return ((close(fd), 0));
		if (ft_strcmp(content, eof) == 0)
		{
			free(content);
			break ;
		}
		ft_putstr_fd(content, fd);
		ft_putstr_fd("\n", fd);
		free(content);
	}
	close(fd);
	return (1);
}

char	*make_filename(unsigned int n)
{
	int		fd;
	char	*num;
	char	*filename;

	n = (int)n;
	num = ft_itoa(n);
	if (num == NULL)
		return (NULL);
	filename = ft_strjoin_v2(BASE_PATH, num);
	free(num);
	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return ((free(filename), NULL));
	close(fd);
	return (filename);
}

int	here_doc(t_data *meta, t_list *tokens)
{
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
	tokens->f_list = alloc_f_list(filename);
	free(filename);
	if (tokens->f_list == NULL)
		return (0);
	if (make_f_list(tokens->token, tokens->f_list[0]) == 0)
	{
		if (meta->stdin_flag == -1)
			return ((reset_stdin_fileno(meta), 0));
		return ((wranning_msg(tokens->token), 0));
	}
	return (1);
}
