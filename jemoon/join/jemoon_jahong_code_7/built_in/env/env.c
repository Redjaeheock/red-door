/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/15 10:24:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	set_underbar(t_data *meta)
{
	t_path	*underbar;

	underbar = add_export("_=/usr/bin/env");
	if (underbar == NULL)
		return ;
	if (check_key(&meta->env, underbar) == 0)
		add_back_export_linked_list(&meta->env, underbar);
}

void	minishell_env(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	int		export_len;

	g_ws = 0;
	export_len = sndry_arr_len((void **)exec_cmd->str);
	if (export_len > 1)
	{
		builtin_error(NULL, 41);
		return ;
	}
	set_underbar(meta);
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (tmp->set != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
