/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:54 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/23 18:52:45 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	check_chdir_error(char *dir)
{
	struct stat	statbuf;

	if (stat(dir, &statbuf) == -1)
	{
		printf("-bash: cd: %s: No such file or directory\n", dir);
		return ;
	}
	if ((statbuf.st_mode != S_IFDIR) || (statbuf.st_mode == 0))
	{
		printf("-bash: cd: %s: Not a directory\n", dir);
		return ;
	}
	if (access(dir, R_OK) == -1)
	{
		printf("cd: permission denied: %s\n", dir);
		return ;
	}
	printf("bash: cd:%s not set\n", dir);
}

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
		check_chdir_error(dir);
	free(dir);
}

