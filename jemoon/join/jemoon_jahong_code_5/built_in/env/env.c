/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/11 13:44:09 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_env(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	int		export_len;

	export_len = sndry_arr_len((void **)exec_cmd->str);
	if (export_len > 1)
	{
		builtin_error(NULL, 41);
		return ;
	}
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (tmp->set != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_ws = 0;
}
