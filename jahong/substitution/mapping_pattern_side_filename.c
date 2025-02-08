/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_pattern_side_filename.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:24:38 by jahong            #+#    #+#             */
/*   Updated: 2025/02/08 11:32:59 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compare_squence_word2(char *f_list, int idx, char **path, int *row)
{
	int	col;
	int	len;

	col = 0;
	len = ft_strlen(path[*row]);
	while ((f_list[idx] != '\0' && path[*row][col] != '\0'))
	{
		printf("row row row = %d %s\n", *row, path[*row]);
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

int	matching_side_pattern(char *f_list, char **path)
{
	int	row;
	int	idx;
	int	f_len;
	int	p_len;

	row = sndry_arr_len((void **)path) - 1;
	idx = 0;
	f_len = ft_strlen(f_list) - 1;
	p_len = ft_strlen(path[row]) - 1;
	printf("comare f_list = %s\n", f_list);
	printf("list last chr = %c | path[%d][%d] = %c\n", f_list[f_len], row, p_len, path[row][p_len]);
	if ((f_list[0] != path[0][0]) || (f_list[f_len] != path[row][p_len]))
		return (0);
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
	if (ft_str_tail_str(f_list, path[row - 1]) == NULL)
	{
		printf("return?????????????????????????????\n");
		return (0);
	}
	return (1);
}

char	**mapping_pattern_side_filname(char **path, char **f_list)
{
	printf("como on code sibal\n");
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
		result = matching_side_pattern(f_list[row], path);
		memo[row] = result + 48;
		row++;
	}
	memo[row] = '\0';
	modify = modify_least_matched_pattern(f_list, memo);
	free(memo);
	return (modify);
}