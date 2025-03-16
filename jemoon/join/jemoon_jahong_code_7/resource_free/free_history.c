/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:00:44 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 15:01:38 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_history_and_free(char **str)
{
	if (*str == NULL)
		return ;
	add_history(*str);
	free(*str);
	*str = NULL;
}
