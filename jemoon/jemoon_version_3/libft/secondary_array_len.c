/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_array_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:57:55 by jahong            #+#    #+#             */
/*   Updated: 2025/01/22 14:09:22 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sndry_arr_len(void **array)
{
	int     len;

	len = 0;
	if (array == NULL)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}
