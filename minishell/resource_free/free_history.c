/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:00:44 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/21 23:33:14 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_history_and_free(char **str)
{
	if (*str == NULL)
		return ;
	if ((*str)[0] != '\0')
	{
		add_history(*str);
		free(*str);
		*str = NULL;
	}
	else
	{
		free(*str);
		*str = NULL;
	}
}
