/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:29 by jahong            #+#    #+#             */
/*   Updated: 2025/02/13 17:00:00 by jahong           ###   ########.fr       */
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

char	**join_path_n_f_list(char **f_list, char **div)
{
	char	**keep;
	
	keep = f_list;
	if (keep != NULL && keep[0] != NULL)
	{
		if (ft_strcmp(keep[0], "Not valid path") != 0)
			f_list = ft_add_str_to_2d_arr(keep, div[2]);
		free_sndry_arr((void **)keep);
	}
	return (f_list);
}
