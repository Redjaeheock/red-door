/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 20:40:09 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	export_part1(t_data *meta, t_cmd_list *exec_cmd, int i, int equal)
{
	t_path	*export_add;
	t_path	*env_add;

	export_add = add_export(exec_cmd->str[i]);
	if (export_add == NULL)
		return ;
	env_add = add_export(exec_cmd->str[i]);
	if (env_add == NULL)
		return ;
	if (equal != 0)
		oldpwd_add(meta, export_add);
	process_export_entry(meta, export_add, env_add, equal);
}

void	export_part2(t_data *meta, t_cmd_list *exec_cmd, int i, int equal)
{
	t_path	*export_add;
	t_path	*env_add;

	export_add = add_plus_export(exec_cmd->str[i]);
	if (export_add == NULL)
		return ;
	env_add = add_plus_export(exec_cmd->str[i]);
	if (env_add == NULL)
		return ;
	if (equal != 0)
		oldpwd_plus_add(meta, export_add);
	process_plus_export_entry(meta, export_add, env_add, equal);
}

void	rest_export(t_data *meta, t_cmd_list *exec_cmd, int export_len)
{
	int	i;
	int	equal;
	int	plus_check;

	i = 1;
	while (i < export_len)
	{
		equal = search_equal(exec_cmd->str[i]);
		plus_check = search_special_characters(exec_cmd->str[i], equal);
		if (plus_check == 1)
		{
			export_part1(meta, exec_cmd, i, equal);
		}
		else if (plus_check == 2)
		{
			export_part2(meta, exec_cmd, i, equal);
		}
		i++;
	}
}
