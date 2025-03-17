/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 12:06:25 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_env(t_data *meta)
{
	t_path	*tmp;
	int		export_len;

	export_len = char_arr_len(meta->exec_cmd->str);
	if (export_len > 1)
	{
		printf("env: %s: No such file or directory\n", meta->exec_cmd->str[1]);
		return ;
	}
	tmp = meta->env;
	while (tmp != NULL)
	{
		if (tmp->set != NULL)
			printf("%s\n", tmp->set);
		tmp = tmp->next;
	}
}
