/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:05:20 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 14:23:35 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**div_f_list_on_slash(char **f_list, char **save)
{
	char	**keep;
	int		row;
	int		len;
	int		idx;
	
	len = sndry_arr_len((void **)f_list);
	keep = (char **)malloc(sizeof(char *) * (len + 1));
	if (keep == NULL)
		return (memory_alloc_error());
	row = 0;
	while (f_list[row] != NULL)
	{
		idx = reverse_conditiona_strlen(f_list[row], '/') + 1;
		if (*save == NULL)
			*save = copy_index_range(f_list[row], 0, idx);
		keep[row] = copy_index_range(f_list[row], idx, ft_strlen(f_list[row]));
		if (keep[row] == NULL)
			return (free_sndry_arr((void **)keep));
		row++;
	}
	keep[row] = NULL;
	return (keep);
}

int	increase_idx_with_chr_in_quote_set(char *path, char c, int idx, int quote)
{
	if (path[idx] == c)
	{
		while (path[idx] == c && path[idx] != '\0')
			idx++;
	}
	else
	{
		while (path[idx] != '\0')
		{
			if (path[idx] == '\'' || path[idx] == '"')
				quote = check_quote_pair(path[idx], quote);
			if (quote == 0 && path[idx] == c)
				break;
			idx++;
		}
	}
	return (idx);
}

char	**take_pattern_in_path(char *path, char **div, int len, char c)
{
	int		row;
	int 	idx;
	int		quote;
	int		start;

	idx = 0;
	row = 0;
	quote = 0;
	start = idx;
	while (path[idx] != 0 && row < len)
	{
		idx = increase_idx_with_chr_in_quote_set(path, c, idx, quote);
		div[row] = copy_index_range_jump_quote(path, start, idx);
		if (div[row] == NULL)
			return (sndry_alloc_err((void **)div));
		start = idx;
		row++;
	}
	div[row] = NULL;
	return (div);
}

char	**quote_conitional_split(char *path, char c)
{
	char	**div;
	char	**keep;
	int		len;
	int		quote;

	quote = 0;
	len = cnt_valid_split_point_chr_in_quote_set(path, c, quote);
	div = (char **)malloc(sizeof(char *) * (len + 1));
	if (div == NULL)
		return (memory_alloc_error());
	div = take_pattern_in_path(path, div, len, c);
	if (div == NULL)
		return (NULL);
	keep = div;
	div = remove_all_same_str(keep, c);
	free_sndry_arr((void **)keep);
	return (div);
}

char	**matching_wildcard_pattern(char *path, char **tmp, char *copy)
{
	char	**div;
	char	**keep;
	int		len;

	len = ft_strlen(path);
	div = quote_conitional_split(path, '*');
	if (div == NULL)
		return (NULL);
	if (path[0] != '*' && path[len - 1] == '*')
		keep = mapping_pattern_start_filname(div, tmp);
	else if (path[0] == '*' && path[len - 1] != '*')
		keep = mapping_pattern_last_filname(div, tmp);
	else if (path[0] != '*' && path[len - 1] != '*')
		keep = mapping_pattern_side_filname(div, tmp);
	else if (path[0] == '*' && path[len - 1] == '*')
		keep = mapping_center_filename(div, tmp);
	free_sndry_arr((void **)div);
	if (copy != NULL && keep != NULL)
	{
		div = keep;
		keep = ft_add_2d_arr_to_str(copy, div);
		free_sndry_arr((void **)div);
	}
	return (keep);
}

