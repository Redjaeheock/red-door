/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:59:10 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 11:52:11 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	check_built_in_cmd(char *cmd, char *exec_cmd)
{
	int	i;

	i = 0;
	if (ft_strlen(cmd) != ft_strlen(exec_cmd))
		return (0);
	while (cmd[i] != '\0' || exec_cmd[i] != '\0')
	{
		if (cmd[i] == exec_cmd[i])
			i++;
		else
			return (0);
	}
	if (cmd[i] != exec_cmd[i])
		return (0);
	return (1);
}
