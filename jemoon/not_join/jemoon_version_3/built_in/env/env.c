/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/22 14:19:41 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell_env(t_data *meta)
{
	t_path	*tmp;

	if (ft_strcmp(meta->exec_cmd->str[0], "env") != 0)
		return ;
	tmp = meta->env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->set);
		tmp = tmp->next;
	}
}

