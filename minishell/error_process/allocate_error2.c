/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_error2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:36:11 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 20:20:59 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*t_path_key_val_alloc_err(t_path *tmp)
{
	printf("Error: Memory access failed! Not Found envp\n");
	free_t_path(tmp);
	g_ws = 1;
	return (NULL);
}

void	*t_list_alloc_err(t_list *tmp)
{
	memory_alloc_error();
	free_t_list(tmp);
	return (NULL);
}

void	*t_tmp_alloc_err(t_tmp *node)
{
	memory_alloc_error();
	free_t_tmp(node);
	g_ws = 1;
	return (NULL);
}

void	*t_data_alloc_err(t_data *meta)
{
	memory_alloc_error();
	free_t_data(meta);
	return (NULL);
}
