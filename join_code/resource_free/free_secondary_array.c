/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_secondary_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:56:30 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 19:33:55 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_multi_2d_arrs(void **array1, void **array2)
{
	int	row;

	if (array1 != NULL)
	{
		row = 0;
		while (array1[row] != NULL)
		{
			free(array1[row]);
			row++;
		}
		free(array1);
	}
	if (array2 != NULL)
	{
		row = 0;
		while (array2[row] != NULL)
		{
			free(array2[row]);
			row++;
		}
		free(array2);
	}
	return (NULL);
}

void	*free_sndry_arr(void **array)
{
	int	row;

	row = 0;
	if (array == NULL)
		return (NULL);
	while (array[row] != NULL)
	{
		free(array[row]);
		row++;
	}
	free(array);
	return (NULL);
}
