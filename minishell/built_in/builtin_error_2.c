/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:13 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/18 21:38:13 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

void	exit_error(char *str, int index)
{
	if (index == 11)
	{
		g_ws = 1;
		printf("-bash: exit: too many arguments\n");
	}
	else if (index == 12)
	{
		g_ws = 2;
		printf("-bash: exit: %s: numeric argument required\n", str);
	}
	return ;
}

void	pwd_error(char *str, int index)
{
	if (index == 31)
	{
		printf("-bash: pwd: %s: invalid option\n", str);
		printf("pwd: usage: pwd [-LP]\n");
	}
	return ;
}

void	env_error(char *str, int index)
{
	if (index == 41)
		printf("-bash: env: too many arguments\n");
	return ;
}

void	export_error(char *str, int index)
{
	if (index == 51)
		printf("-bash: export: `%s': not a valid identifier\n", str);
	return ;
}

void	unset_error(char *str, int index)
{
	if (index == 61)
	{
		printf("-bash: unset: `%s': not a valid identifier\n", str);
	}
	if (index == 62)
	{
		printf("-bash: unset: %s: invalid option\n", str);
		printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
	}
	return ;
}
