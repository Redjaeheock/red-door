/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 20:12:10 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	minishell_pwd(t_data *meta)
{
	char *str;

	if (ft_strcmp(meta->exec_cmd->str[0], "PWD") != 0)
		return ;
	str = searching_from_envval(meta, "PWD");
	printf("%s\n", str);
	free(str);
	str = NULL;
}
