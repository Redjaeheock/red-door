/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_pattern_start_n_center_filename.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:09:45 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 14:17:02 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_squence_word1(char *f_list, int idx, char **path, int *row)
{
	int	col;
	int	len;

	col = 0;
	len = ft_strlen(path[*row]);
	while ((f_list[idx] != '\0' && path[*row][col] != '\0'))
	{
		if (f_list[idx] == path[*row][col])
		{
			col++;
			idx++;
			if (col == len)
			{
				*row += 1;
				return (idx - 1);
			}
		}
		else
		{
			idx += 1 - col;
			col = 0;
		}
	}
	return (ft_strlen(f_list));
}

int	matching_fisrt_pattern(char *f_list, char **path)
{
	int	row;
	int	idx;

	row = 0;
	idx = 0;
	if (f_list[0] != path[row][0])
		return (0);
	while (f_list[idx] != '\0' && path[row] != NULL)
	{
		idx = compare_squence_word1(f_list, idx, path, &row);
		if (idx == ft_strlen(f_list))
			return (0);
		if (row == sndry_arr_len((void **)path))
			break ;
		idx++;
	}
	return (1);
}

char	**mapping_pattern_start_filname(char **path, char **f_list)
{
	char	**modify;
	char	*memo;
	int		len;
	int		row;
	int		result;

	len = sndry_arr_len((void **)f_list);
	memo = (char *)malloc(sizeof(char) * (len + 1));
	if (memo == NULL)
		return (memory_alloc_error());
	row = 0;
	while (f_list[row] != NULL)
	{
		result = matching_fisrt_pattern(f_list[row], path);
		memo[row] = result + 48;
		row++;
	}
	memo[row] = '\0';
	if (conditional_jump_len(memo, '1') == 0)
		return ((free(memo), NULL));
	modify = modify_least_matched_pattern(f_list, memo);
	free(memo);
	return (modify);
}

int	matching_center_pattern(char *f_list, char **path)
{
	int	row;
	int	idx;

	idx = 0;
	row = 0;
	while (f_list[idx] != '\0' && path[row] != NULL)
	{
		idx = compare_squence_word1(f_list, idx, path, &row);
		if (idx == ft_strlen(f_list))
			return (0);
		if (row == sndry_arr_len((void **)path))
			break ;
		idx++;
	}
	if (idx == ft_strlen(f_list) && row != sndry_arr_len((void **)path))
		return (0);
	return (1);
}

char	**mapping_center_filename(char **path, char **f_list)
{
	char	**modify;
	char	*memo;
	int		row;
	int		result;
	int		len;

	len = sndry_arr_len((void **)f_list);
	memo = (char *)malloc(sizeof(char) * (len + 1));
	if (memo == NULL)
		return (memory_alloc_error());
	row = 0;
	while (f_list[row] != NULL)
	{
		result = matching_center_pattern(f_list[row], path);
		memo[row] = result + 48;
		row++;
	}
	memo[row] = '\0';
	if (conditional_jump_len(memo, '1') == 0)
		return ((free(memo), NULL));
	modify = modify_least_matched_pattern(f_list, memo);
	free(memo);
	return (modify);
}
