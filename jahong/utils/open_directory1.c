/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:29 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 14:21:19 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**open_path_low_rank(char **path)
{
	char	**f_list;
	char	**keep;
	char	**keep2;
	int		row;

	row = 0;
	f_list = NULL;
	while (path[row] != NULL)
	{
		if (count_file_in_directory(path[row]) != 0)
		{
			keep2 = get_path_filelist(path[row]);
			if (keep2 == NULL)
				return (free_sndry_arr((void **)f_list));
		}
		else
			keep2 = NULL;
		keep = ft_merge_2d_arr(f_list, keep2);
		free_multi_2d_arrs((void **)keep2, (void **)f_list);
		if (keep == NULL)
			return (NULL);
		f_list = keep;
		row++;
	}
	return (f_list);
}

char	**open_root_directory(char *path, int p_len)
{
	char	**f_list;
	char	**keep;
	char	**div;
	int		row;

	row = 0;
	if (ft_strlen(path) == 1)
		f_list = get_root_filelist();
	else if (p_len == 1)
	{
		div = split_last_slash_path(path);
		if (div == NULL)
			return (NULL);
		keep = get_path_filelist(div[0]);
		if (keep == NULL)
			return (sndry_alloc_err((void **)div));
		f_list = mapping_pattern_filename(div[1], keep);
		free_sndry_arr((void **)keep);
		if (sndry_arr_len((void **)div) == 3)
		f_list = join_path_n_f_list(f_list, div);
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

char	**open_multi_directory(char *path, char **f_list)
{
	char 	**keep;
	char	**tmp;
	char	*copy;
	
	copy = NULL;
	if (check_chr_not_quote_set(path, '*') == 1)
	{
		if (search_chr_in_str(f_list[0], '/') == 1)
			tmp = div_f_list_on_slash(f_list, &copy);
		else
			tmp = f_list;
		if (tmp == NULL)
			return (NULL);
		keep = matching_wildcard_pattern(path, tmp, copy);
	}
	else
	{
		copy = copy_index_range_jump_quote(path, 0, ft_strlen(path));
		if (copy == NULL)
			return (NULL);
		keep = mapping_pattern_filename(copy, f_list);
	}
	if (tmp != f_list)
		free_sndry_arr((void **)tmp);
	return ((free(copy), keep));
}