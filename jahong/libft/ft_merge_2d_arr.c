/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_2d_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:09:37 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 16:37:54 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**merge_arr(char **merge, char **src, int *row)
{
	int	n;

	n = 0;
	while (src != NULL && src[n] != NULL)
	{
		merge[*row] = ft_strdup(src[n]);
		if (merge[*row] == NULL)
		{
			merge = sndry_alloc_err((void **)merge);
			break ;
		}
		*row += 1;
		n++;
	}
	return (merge);
}

char	**ft_merge_2d_arr(char **arr1, char **arr2)
{
	char	**merge;
	int		len;
	int		row;
	int		n;

	row = 0;
	len = sndry_arr_len((void **)arr1) + sndry_arr_len((void **)arr2);
	merge = (char **)malloc(sizeof(char *) * (len + 1));
	if (merge == NULL)
		return (memory_alloc_error());
	merge = merge_arr(merge, arr1, &row);
	if (merge == NULL)
		return (NULL);
	merge = merge_arr(merge, arr2, &row);
	if (merge == NULL)
		return (NULL);
	merge[row] = NULL;
	return (merge);
}
