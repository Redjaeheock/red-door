/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_error2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:36:11 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 17:00:32 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*t_tmp_alloc_err(t_tmp *node)
{
	memory_alloc_error();
	free_tmp_list(node);
	return (NULL);
}