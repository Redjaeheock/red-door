/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:28:31 by jahong            #+#    #+#             */
/*   Updated: 2025/03/22 16:41:06 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BASE_PATH "/tmp/"
#define UNSIGNED_INT_MAX 4294967295

char	*make_filename(unsigned int n)
{
	int		fd;
	char	*num;
	char	*filename;

	n = (int)n;       // unsign 범위 수용 못함 수정 필요
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

char	**alloc_f_list(void)
{
	char			**f_list;
	char			*filename;
	unsigned int	cnt;

	cnt = 0;
	while (1)
	{
		filename = make_filename(cnt);
		if (filename != NULL)
			break ;
		else if (filename == NULL && cnt == UNSIGNED_INT_MAX)
			return ((printf("System error of use buffer\n"), NULL));
		cnt++;
	}
	f_list = (char **)malloc(sizeof(char *) * 2);
	if (f_list == NULL)
		return (memory_alloc_error());
	f_list[0] = ft_strdup(filename);
	free(filename);
	if (f_list[0] == NULL)
		return (sndry_alloc_err((void **)f_list));
	f_list[1] = NULL;
	return (f_list);
}

int	write_heredoc_buffer(t_data *meta, char *str, int fd)
{
	t_tmp	*tmp;
	char	**div;
	int		result;

	if (search_chr_in_str(str, '$') == 0)
	{
		if (ft_strcmp(str, "") != 0)
			ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		return (1);
	}
	result = measure_length_quote_set(str, result = 0, 'h');
	div = dividing_sub_token(str, result);
	if (div == NULL)
		return (0);
	tmp = do_substitute_dollar_sign(meta, div, 'h');
	free_sndry_arr((void **)div);
	if (tmp == NULL)
		return (0);
	result = join_sub_tokens(NULL, tmp, 'h', fd);
	free_t_tmp(tmp);
	if (result == 0)
		return (0);
	return (1);
}

int	make_f_list(t_data *meta, char *eof, char *filename)
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
		if (write_heredoc_buffer(meta, content, fd) == 0)
			return ((free(content), close(fd), 0));
		free(content);
	}
	return ((close(fd), 1));
}

int	here_doc(t_data *meta, t_list *tokens)
{
	char			*filename;

	tokens->f_list = alloc_f_list();
	if (tokens->f_list == NULL)
		return (0);
	if (make_f_list(meta, tokens->token, tokens->f_list[0]) == 0)
	{
		if (meta->stdin_flag == -1)
		{
			dup2(meta->oldstdin, STDIN_FILENO);
			close(meta->oldstdin);
			return (0);
		}
		return ((wranning_msg(tokens->token), 0));
	}
	return (1);
}
