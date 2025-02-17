/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 10:45:50 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	rest_export(t_data *meta, int export_len)
{
	int		i;
	int		equal;
	t_path	*export_add;
	t_path	*env_add;

	i = 1;
	while (i < export_len)
	{
		equal = search_equal(meta->exec_cmd->str[i]);
		if (search_special_characters(meta->exec_cmd->str[i]) == 1)
		{
			export_add = add_export(meta->exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_export(meta->exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
			process_export_entry(meta, export_add, env_add, equal);
		}
		i++;
	}
}
