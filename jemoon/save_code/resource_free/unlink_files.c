/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:08 by jahong            #+#    #+#             */
/*   Updated: 2025/02/21 20:37:01 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unlink_files(t_list	*tokens)
{
	while (tokens != NULL)
	{
		if (ft_strcmp(tokens->token, "<<") == 0)
		{
			if (tokens->f_list != NULL)
				unlink(tokens->f_list[0]);
		}
		tokens = tokens->next;
	}
}
