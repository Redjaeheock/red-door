/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_disosable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 23:40:11 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*initialize_oldpwd(t_path *tmp)
{
	char	*str;

	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			if (tmp->value == NULL)
				break ;
			str = ft_strdup(tmp->value);
			if (str == NULL)
				return (memory_alloc_error());
			return (str);
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		str = change_null_string();
		if (str == NULL)
			return (memory_alloc_error());
		return (str);
	}
	return (NULL);
}
