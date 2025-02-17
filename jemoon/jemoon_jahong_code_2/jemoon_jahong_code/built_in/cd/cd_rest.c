/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:54 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/14 19:13:47 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	cd_rest(t_data *meta, char *str)
{
	char	*pwd;
	char	*dir;

	dir = set_dir(meta, str);
	if (dir == NULL)
		return ;
	if (chdir(dir) == 0)
	{
		pwd = redefine_pwd(meta, dir);
		redefine_export(&meta->exp, pwd);
		redefine_export(&meta->env, pwd);
		free(meta->pwd);
		meta->pwd = NULL;
		meta->pwd = ft_strdup(pwd);
		free(pwd);
		pwd = NULL;
	}
	else
		printf("bash: cd:%s not set\n", dir);
	free(dir);
}
