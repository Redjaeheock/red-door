/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:12:51 by jahong            #+#    #+#             */
/*   Updated: 2025/02/05 10:11:06 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_valid_head_pattern_filename(char **list, char *str)
{
	int	row;
	int	cnt;

	row = 0;
	cnt = 0;
	while (list[row] != NULL)
	{
		if (ft_str_head_str(list[row], str) != NULL)
			cnt++;
		row++;
	}
	return (cnt);
}

int	count_valid_tail_pattern_filename(char **list, char *str)
{
	int	row;
	int	cnt;

	row = 0;
	cnt = 0;
	while (list[row] != NULL)
	{
		if (ft_str_tail_str(list[row], str) != NULL)
			cnt++;
		row++;
	}
	return (cnt);
}

int	search_str_in_f_list(t_list *node, char **list, char *str)
{
	int		row;
	int		len;
	int		n;

	row = 0;
	n = 0;
	printf("[[[[[[[[[ searching filename = %s ]]]]]]]]\n", str);
	len = count_valid_tail_pattern_filename(list, str);
	node->f_list = (char **)malloc(sizeof(char *) * (len + 1));
	if (node->f_list == NULL)
		return ((memory_alloc_error(), -1));
	while (list[row] != NULL)
	{
		if (ft_str_tail_str(list[row], str) != NULL)
		{
			node->f_list[n] = ft_strdup(list[row]);
			if (node->f_list[n++] == NULL)
			{
				node->f_list = sndry_alloc_err((void **)node->f_list);
				return (-1);
			}
		}
		row++;
	}
	node->f_list[n] = NULL;
	return (1);
}

char	**take_filenames_basic(struct dirent *entry, DIR *dir, int len)
{
	char	**tmp;
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
			if (tmp[row] == NULL)
				return (sndry_alloc_err((void **)tmp));
			row++;
		}
		entry = readdir(dir);
	}
	tmp[row] = NULL;
	if (row != len)
		return (sndry_alloc_err((void **)tmp));
	return (tmp);
}

char	**open_n_read_filenames(char *path, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**f_list;
	char			**fail;

	fail = (char **)malloc(sizeof(char *) * 2);
	if (fail == NULL)
		return (NULL);
	fail[0] = ft_strdup("no such path");
	fail[1] = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "/") == 0)
		{
			printf("system error: fail open directory\n");
			return (free_sndry_arr((void **)fail));
		}
		return (fail);
	}
	free_sndry_arr((void **)fail);
	entry = readdir(dir);
	f_list = take_filenames_basic(entry, dir, len);
	closedir(dir);
	if (f_list == NULL)
		return (NULL);
	return (f_list);
}

int	count_file_in_directory(char	*path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				cnt;

	dir = opendir(path);
	if (dir == NULL)
	{
		if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "/") == 0)
			return ((printf("system error: fail open directory\n"), -1));
		return (0);
	}
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
