/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:12:51 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 18:53:48 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_valid_filename(char **list, char *str)
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
	len = count_valid_filename(list, str);
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

char	**take_filenames1(struct dirent *entry, DIR *dir, int len)
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

int	open_n_read_current_filenames(t_list *node, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**f_list;

	dir = opendir(".");
	if (dir == NULL)
		return ((printf("system error: fail open directory\n"), -1)); // . 으로 연 경로가 실패하는 건 시스템 문제제
	entry = readdir(dir);
	f_list = take_filenames1(entry, dir, len);
	if (f_list == NULL)
		return ((closedir(dir), -1));
	node->f_list = f_list;
	closedir(dir);
	return (1);
}

int	open_n_filter_current_filenames(t_list *node, char *str, int len)
{
	char	**f_list;
	int		result;

	result = open_n_read_current_filenames(node, len);
	if (node->f_list == NULL)
		return (-1);
	f_list = node->f_list;
	result = search_str_in_f_list(node, f_list, str);
	printf("^*^*^*^*^*^*NMNM node->f_list[0] = %s|MNMMNNM\n", node->f_list[0]);
	sndry_alloc_err((void **)f_list);
	return (result);
}

int	count_list_current_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				cnt;

	dir = opendir(".");
	if (dir == NULL)
		return ((printf("system error fail open directory\n"), -1));
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