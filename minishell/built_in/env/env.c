/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 18:00:16 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_env(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	t_path	*underbar_tmp;
	int		export_len;

	g_ws = 0;
	underbar_tmp = NULL;
	export_len = sndry_arr_len((void **)exec_cmd->str);
	if (export_len > 1)
	{
		builtin_error(NULL, 41);
		return ;
	}
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (tmp->set != NULL && ft_strcmp(tmp->key, "_") != 0)
			printf("%s=%s\n", tmp->key, tmp->value);
		else if (tmp->set != NULL && ft_strcmp(tmp->key, "_") == 0)
			underbar_tmp = tmp;
		tmp = tmp->next;
	}
	if (underbar_tmp != NULL)
		printf("%s=%s\n", underbar_tmp->key, underbar_tmp->value);
}
