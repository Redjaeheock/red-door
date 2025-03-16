/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_pattern_filename.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:53:58 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:11:32 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**extract_path_in_f_list(char **f_list, char *path, int len)
{
	char	**keep;
	int		row;
	int		n;

	keep = (char **)malloc(sizeof(char *) * (len + 1));
	if (keep == NULL)
		return (memory_alloc_error());
	row = 0;
	n = 0;
	while (f_list[row] != NULL)
	{
		if (ft_strcmp(f_list[row], path) == 0)
		{
			keep[n] = ft_strdup(f_list[row]);
			if (keep[n] == NULL)
				return (free_sndry_arr((void **)keep));
			n++;
		}
		row++;
	}
	keep[n] = NULL;
	return (keep);
}

int	count_path_in_f_list(char **f_list, char *path)
{
	int		row;
	int		len;

	row = 0;
	len = 0;
	while (f_list[row] != NULL)
	{
		if (ft_strcmp(f_list[row], path) == 0)
			len++;
		row++;
	}
	return (len);
}

char	**mapping_pattern_filename(char *path, char **f_list)
{
	char	**keep;
	int		len;

	len = count_path_in_f_list(f_list, path);
	if (len == -1)
		return (NULL);
	//경로 유효한 게 없을 때의 경우 설정해두기
	keep = extract_path_in_f_list(f_list, path, len);
	if (keep == NULL)
		return (NULL);
	return (keep);
}
