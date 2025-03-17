/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:15:00 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 17:12:39 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	minishell_echo(t_cmd_list **exec_cmd)
{
	int	i;

	i = 0;
	if (check_built_in_cmd("echo", (*exec_cmd)->str[i++]) == 0)
		return ;
	if (check_option_n((*exec_cmd)->str[i]) == 1)
	{
		i++;
		while ((*exec_cmd)->str[i] != NULL)
		{
			printf("%s", (*exec_cmd)->str[i]);
			i++;
		}
		return ;
	}
	else
	{
		while ((*exec_cmd)->str[i] != NULL)
		{
			printf("%s", (*exec_cmd)->str[i]);
			i++;
		}
		printf("\n");
		return ;
	}
}
