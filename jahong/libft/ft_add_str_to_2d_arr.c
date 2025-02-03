/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_2d_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:19:11 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 17:38:46 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_add_str_to_2d_arr(char **arr, char *str)
{
	char	**join;
	int		len;
	int		row;

	len = sndry_arr_len((void **)arr);
	join = (char **)malloc(sizeof(char *) * (len + 1));
	if (join == NULL)
		return (NULL);
	row = 0;
	while (arr[row] != NULL)
	{
		join[row] = ft_strjoin_v2(arr[row], str);
		if (join[row] == NULL)
			return (free_sndry_arr((void **)arr));
		row++;
	}
	join[row] = NULL;
	return (join);
}