/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:28:07 by jahong            #+#    #+#             */
/*   Updated: 2025/01/25 21:36:25 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_d_list(char **filelist)
{
	char	*str1;
	char	*str2;
	int		row;

	str1 = NULL;
	row = 0;
	while (filelist[row] != NULL)
	{
		str2 = ft_strjoin_v2(str1, filelist[row]);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		row++;
	}
	return (str1);
}

char	**take_filenames1(struct dirent *entry, DIR *dir, char *path, int len)
{
	char	**tmp;
	char	*join;
	int		row;

	row = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (memory_alloc_error());
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			tmp[row] = ft_strdup(entry->d_name);
			// printf("-0--0-0--0-0--0-0--0-tmp[row] = %s\n", tmp[row]);
			if (tmp[row] == NULL)
				return (sndry_alloc_err((void **)tmp));
			row++;
		}
		entry = readdir(dir);
	}
	tmp[row] = NULL;
	return (tmp);
}

int	open_n_read_filenames1(t_list *node, char *path, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**d_list;
	int				row;

	dir = opendir(path);
	if (dir == NULL)
		return ((printf("system error file open directory\n"), -1));
	entry = readdir(dir);
	if (entry == NULL)
		return (closedir(dir), 0);
	d_list = take_filenames1(entry, dir, path, len);
	if (d_list == NULL)
		return (closedir(dir), -1);
	free(node->token);
	node->token = join_d_list(d_list);
	if (node->token == NULL)
		return (closedir(dir), -1);
	closedir(dir);
	return (1);
}

int	count_list_current_directory(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				cnt;

	dir = opendir(path);
	if (dir == NULL)
		return ((printf("system error file open directory\n"), -1));
	entry = readdir(dir);
	if (entry == NULL)
		return ((closedir(dir), 0));
	cnt = 0;
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			cnt++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (cnt);
}

char	*search_value_using_key(t_path *path, char *src)
{
	char *str;

	str = "";
	while (path != NULL)
	{
		if (strcmp(path->key, src) == 0)
		{
			str = ft_strdup(src);
			if (str == NULL)
				return (memory_alloc_error());
			break ;
		}
		path = path->next;
	}
	return (str);
}

char *copy_index_range(char *str, int idx, int end)
{
	char	*tmp;
	int		n;
	int		len;

	n = 0;
	len = end - idx;
	if (end != ft_strlen(str))
		len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		tmp[n] = str[idx];
		idx++;
		n++;
	}
	tmp[n] = '\0';
	return (tmp);
}
int	ck_part_of_special_chr(int c)
{
	if ('!' <= c && c <= '/')
		return (1);
	if (c == ':' || c == ';')
		return (1);
	if (c == '=' || c == '@')
		return (1);
	if ('[' <= c && c <= '^')
		return (1);
	if (c == '`' || ('{' <= c && c <= '~'))
		return (1);
	return (0);
}