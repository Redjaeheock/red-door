/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_as_file2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:28:40 by jahong            #+#    #+#             */
/*   Updated: 2025/02/08 09:17:50 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**div_last_slash_path(char *path, int len, int idx)
{
	char	**div;
	char	row;
	int		start;

	div = (char **)malloc(sizeof(char *) * (len + 1));
	if (div == NULL)
		return (memory_alloc_error());
	row = 0;
	start = 0;
	while (row < len)
	{
		printf("row = %d ||| idx ===%d %c\n", row, idx, path[idx]);
		div[row] = copy_index_range(path, start, idx);
		if (div[row] == NULL)
			return (sndry_alloc_err((void **)div));
		start = idx;
		if (path[idx] == '/')
			idx++;
		while (path[idx] != '/' && path[idx] != '\0')
			idx++;
		row++;
	}
	div[row] = NULL;
	return (div);
}

char	**split_last_slash_path(char *path)
{
	char	**div;
	int		idx;
	int		len;

	idx = ft_strlen(path) - 1;
	if (path[idx] == '/')
	{
		len = 3;
		while (0 <= idx)
		{
			idx--;
			if (path[idx] == '/')
				break ;
		}
		printf("-----idx = %d==\n", idx);
		div = div_last_slash_path(path, len, idx + 1);
	}
	else
	{
		len = 2;
		idx = reverse_conditiona_strlen(path, '/');
		div = div_last_slash_path(path, len, idx + 1);
	}
	return (div);
}

int	change_only_wildcard_token(t_list *node)
{
	char	**tmp;
	int		result;
	int		cnt;

	cnt = count_file_in_directory(".");
	if (cnt == -1)
		return (cnt);
	tmp = open_n_read_filenames(".", cnt);
	if (tmp == NULL)
		return (-1);
	node->f_list = tmp;
	return (1);
}

char	**get_root_filelist(void)
{
	char	**f_list;
	int		len;

	len = count_file_in_directory("/");
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames("/", len);
	return (f_list);
}

char	**get_current_filelist(void)
{
	char	**f_list;
	int		len;
	printf("here?\n");
	len = count_file_in_directory(".");
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames(".", len);
	return (f_list);
}
char	**get_path_filelist(char *path)
{
	char	**f_list;
	int		len;
	len = count_file_in_directory(path);
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames(path, len);
	return (f_list);
}


char	**open_root_directory(char *path, int p_len)
{
	char	**f_list;
	char	**keep;
	char	**div;
	int		row;
	int idx = 0;

	row = 0;
	if (ft_strlen(path) == 1)
		f_list = get_root_filelist();
	else if (p_len == 1)
	{
		div = split_last_slash_path(path);
		if (div == NULL)
			return (NULL);
		while (div[idx] != NULL)
		{
			printf("div = %s\n", div[idx]);
			idx++;
		}
		keep = get_path_filelist(div[0]);
		if (keep == NULL)
			return (sndry_alloc_err((void **)div));
		f_list = mapping_pattern_filename(div[1], keep);
		free_sndry_arr((void **)keep);
		if (sndry_arr_len((void **)div) == 3)
		{
			keep = f_list;
			if ((keep != NULL && keep[0] != NULL) && ft_strcmp(keep[0], "Not valid path") != 0)
			{
				f_list = ft_add_str_to_2d_arr(keep, div[2]);
				free_sndry_arr((void **)keep);
			}
		}
		free_sndry_arr((void **)div);
	}
	else
		f_list = get_path_filelist(path);
	return (f_list);
}

char	**open_wildcard_directory(char *path)
{
	char	**f_list;
	char	**keep;

	f_list = get_current_filelist();
	if (are_all_characters_same(path, '*') != 1)
	{
		keep = open_multi_directory(path, f_list);
		free_sndry_arr((void **)f_list);
		f_list = keep;
	}
	return (f_list);

}
char **open_current_directory(char *path)
{
	char	**f_list;
	char	**keep;

	if (search_chr_in_str(path, '/') == 1)
		f_list = get_path_filelist(path);
	else
	{
		f_list = get_current_filelist();
		keep = open_multi_directory(path, f_list);
		free_sndry_arr((void **)f_list);
		f_list = keep;
	}
	return (f_list);
}