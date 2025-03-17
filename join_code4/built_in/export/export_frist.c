/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_frist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 00:43:55 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	frist_export(t_data *meta)
{
	t_path	*temp;
	int		equal;

	sort_export(&meta->exp);
	temp = meta->exp;
	while (temp != NULL)
	{
		equal = search_equal(temp->set);
		if (ft_strcmp(temp->key, "_") == 0)
		{
			temp = temp->next;
			continue ;
		}
		if (equal == 0)
			printf("declare -x %s\n", temp->set);
		else
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}
