/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:07 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 16:23:17 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell_exit(t_data *meta)
{
	if (check_built_in_cmd("exit", meta->exec_cmd->str[0]) == 0)
		return ;
	printf("exit\n");
	free_env_resource(meta);
	exit (1);
}
