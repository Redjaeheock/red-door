/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/24 15:36:47 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_env(t_data *meta, t_cmd_list *exec_cmd)
{
	t_path	*tmp;
	int		export_len;

	export_len = char_arr_len(exec_cmd->str);
	if (export_len > 1)
	{
		printf("env: %s: No such file or directory\n", exec_cmd->str[1]);
		return ;
	}
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (tmp->set != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
