/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 16:01:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

char	*get_cd_dir(t_data *meta, char *str)
{
	char	*dir;

	if (str == NULL)
	{
		dir = ft_strdup(meta->home);
		if (dir == NULL)
		{
			printf("bash: cd:HOME not set\n");
			return (NULL);
		}
	}
	else
	{
		dir = set_dir(meta, str);
		if (dir == NULL)
			return (NULL);
	}
	return (dir);
}

void	cd_execute(t_data *meta, char *str)
{
	char	*pwd;
	char	*dir;

	dir = get_cd_dir(meta, str);
	if (dir == NULL)
		return ;
	if (chdir(dir) == 0)
	{
		pwd = redefine_pwd(meta, dir);
		redefine_export(meta, &meta->exp, pwd);
		redefine_export(meta, &meta->env, pwd);
		free(meta->oldpwd);
		meta->oldpwd = NULL;
		meta->oldpwd = ft_strdup(meta->pwd);
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
