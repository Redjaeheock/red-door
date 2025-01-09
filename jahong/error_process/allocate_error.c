/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:42:04 by jahong            #+#    #+#             */
/*   Updated: 2025/01/09 16:04:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*t_path_key_val_alloc_err(t_path *tmp)
{
	printf("Error: Memory allocation failed! Not Found envp\n");
	free_key_value(tmp);
	free_t_path(tmp);
	return (NULL);
}
void	*t_list_alloc_err(t_list *tmp)
{
	printf("Error: Memory allocation failed!\n");
	free_t_list(tmp);
	return (NULL);
}
void	*sndry_alloc_err(void **arr)
{
	printf("Error: Memory allocation failed!\n");
	free_sndry_arr(arr);
	return (NULL);
}
void	*t_data_alloc_err(t_data *meta)
{
	printf("Error: Memory allocation failed!\n");
	free_t_data(meta);
	return (NULL);
}