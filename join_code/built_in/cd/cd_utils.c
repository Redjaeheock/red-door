/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:57:08 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/24 16:07:51 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

char	*get_env(t_path *env, char *home)
{
	t_path	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, home) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

int	find_node(t_path *env, char *key)
{
	t_path	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
