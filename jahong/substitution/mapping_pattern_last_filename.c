/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_pattern_last_filename.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:21:12 by jahong            #+#    #+#             */
/*   Updated: 2025/02/13 10:06:05 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_reverse_word(char *f_list, int idx, char **path, int *row)
{
	int	col;

	col = ft_strlen(path[*row]) - 1;
	printf("compare word = %s\n", path[*row]);
	while (0 <= idx && 0 <= col)
	{
		if (f_list[idx] == path[*row][col])
		{
			col--;
			idx--;
			if (col == -1)
			{
				*row -= 1;
				return (idx + 1);
			}
		}
		else
		{
			col = ft_strlen(path[*row]) - 1;
			idx -= 1 + col;
		}
	}
	return (ft_strlen(f_list));
}

int	matching_last_pattern(char *f_list, char **path)
{
	int	row;
	int	idx;
	int	len;

	row = sndry_arr_len((void **)path) - 1;
	idx = ft_strlen(f_list) - 1;
	len = ft_strlen(path[row]) - 1;
	if (f_list[idx] != path[row][len])
		return (0);
	while (0 <= idx)
	{
		idx = compare_reverse_word(f_list, idx, path, &row);
		if (idx == ft_strlen(f_list))
			return (0);
		if (row == -1)
			break ;
		idx--;
	}
	if (idx == ft_strlen(f_list) && row != sndry_arr_len((void **)path))
		return (0);
	return (1);
}

char	**mapping_pattern_last_filname(char **path, char **f_list)
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
		result = matching_last_pattern(f_list[row], path);
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
