/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:13 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/13 21:22:45 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "built_in.h"

void	cd_error(char *str, int index)
{
	if (index == 71)
		printf("bash: cd: too many arguments\n");
	if (index == 72)
		printf("bash: cd: %s: No such file or directory\n", str);
	if (index == 74)
		printf("bash: cd:HOME not set\n");
	if (index == 75)
		printf("bash: cd: %s: Permission denied\n", str);
	return ;
}

void	builtin_error(char *str, int index)
{
	g_ws = 1;
	if (11 <= index && index <= 20)
		exit_error(str, index);
	if (31 <= index && index <= 40)
		pwd_error(str, index);
	if (41 <= index && index <= 50)
		env_error(str, index);
	if (51 <= index && index <= 60)
		export_error(str, index);
	if (61 <= index && index <= 70)
		unset_error(str, index);
	if (71 <= index && index <= 80)
		cd_error(str, index);
	return ;
}
