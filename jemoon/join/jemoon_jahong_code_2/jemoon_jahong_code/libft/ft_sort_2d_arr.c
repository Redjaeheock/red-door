/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_2d_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:23:24 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 19:21:16 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_2d_arr(char **str)
{
	char	*tmp;
	int		row1;
	int		row2;
	int		len;

	row1 = 0;
	while (str[row1] != NULL)
	{
		len = ft_strlen(str[row1]);
		row2 = row1 + 1;
		while (str[row2] != NULL)
		{
			if (ft_strncmp(str[row1], str[row2], len) > 0)
			{
				tmp = str[row1];
				str[row1] = str[row2];
				str[row2] = tmp;
			}
			row2++;
		}
		row1++;
	}
}
