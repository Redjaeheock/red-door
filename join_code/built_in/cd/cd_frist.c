/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_frist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/24 18:02:05 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	cd_home(t_data *meta)
{
	char	*home;

	home = ft_strdup(meta->home);
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
	free(home);
}
