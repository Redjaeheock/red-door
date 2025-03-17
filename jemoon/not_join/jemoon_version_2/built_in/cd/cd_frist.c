/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_frist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/01 14:08:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_home(t_data *meta)
{
	char	*home;

	home = get_env(meta->env, "HOME");
	if (home == NULL)
	{
		printf("bash: cd:HOME not set\n");
		return ;
	}
	if (chdir(home) == 0)
	{
		redefine_export(&meta->exp, home);
		redefine_export(&meta->env, home);
	}
	else
		printf("bash: cd:%s not set\n", home);
}
