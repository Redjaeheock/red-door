/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:07:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 17:43:29 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	set_null_by_key(t_path **exp, char *key)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp((temp)->key, key) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_value_by_key(t_path **exp, char *key, char *value)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			temp->value = ft_strdup(value);
			free(temp->set);
			temp->set = NULL;
			temp->set = ft_strjoin_v2(temp->key, "=");
			temp->set = ft_strjoin(temp->set, temp->value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_free_by_key(t_path **exp, char *key)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp((temp)->key, key) == 0)
		{
			if (temp->value != NULL)
			{
				free(temp->value);
				temp->value = NULL;
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
