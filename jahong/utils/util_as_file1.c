/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_as_file1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:12:51 by jahong            #+#    #+#             */
/*   Updated: 2025/02/13 17:36:28 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**alloc_fail_msg(void)
{
	char	**msg;

	msg = (char **)malloc(sizeof(char *) * 2);
	if (msg == NULL)
		return (memory_alloc_error());
	msg[0] = ft_strdup("Not valid path");
	if (msg[0] == NULL)
		return (sndry_alloc_err((void **)msg));
	else 
		msg[1] = NULL;
	return (msg);
}

char	**open_n_read_filenames(char *path, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**f_list;
	char			**fail;

	fail = alloc_fail_msg();
	if (fail == NULL)
		return (NULL);
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

int	count_file_in_directory(char *path)
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
