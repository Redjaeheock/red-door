/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_array_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:56:30 by jahong            #+#    #+#             */
/*   Updated: 2025/01/06 16:30:47 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_sndry_arr(void **array)
{
	int     row;

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