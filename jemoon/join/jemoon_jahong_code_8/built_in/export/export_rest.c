/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 20:32:50 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	rest_export(t_data *meta, t_cmd_list *exec_cmd, int export_len)
{
	int		i;
	int		equal;
	int		plus_check;
	t_path	*export_add;
	t_path	*env_add;

	i = 1;
	while (i < export_len)
	{
		equal = search_equal(exec_cmd->str[i]);
		plus_check = search_special_characters(exec_cmd->str[i], equal);
		if (plus_check == 1)
		{
			export_add = add_export(exec_cmd->str[i]);
			if (export_add == NULL)
				return ;
			env_add = add_export(exec_cmd->str[i]);
			if (env_add == NULL)
				return ;
			oldpwd_add(meta, export_add);
			process_export_entry(meta, export_add, env_add, equal);
		}
		else if (plus_check == 2)
		{
			
		}
		i++;
	}
}
