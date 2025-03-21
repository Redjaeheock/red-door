/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_error1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:42:04 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 20:18:46 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*memory_alloc_error(void)
{
	printf("Error: Memory access failed!\n");
	g_ws = 1;
	return (NULL);
}

void	*sndry_alloc_err(void **arr)
{
	memory_alloc_error();
	free_sndry_arr(arr);
	return (NULL);
}
