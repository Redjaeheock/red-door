/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 16:52:21 by jemoon           ###   ########.fr       */
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
		dir = get_env(meta->env, "HOME");
		if (dir == NULL)
		{
			builtin_error(NULL, 74);
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

int	check_exec_permission(char *dir)
{
	if (access(dir, X_OK) == -1)
	{
		builtin_error(dir, 75);
		free(dir);
		return (0);
	}
	return (1);
}

int	check_exec_stat(char *dir)
{
	struct stat	sb;

	if (stat(dir, &sb) == -1)
	{
		builtin_error(dir, 72);
		free(dir);
		return (0);
	}
	return (1);
}

void	change_directory(t_data *meta, char *dir)
{
	char	*pwd;

	if (chdir(dir) == 0)
	{
		pwd = redefine_pwd(meta, dir);
		redefine_export(meta, &meta->exp, pwd);
		redefine_export(meta, &meta->env, pwd);
		free(meta->oldpwd);
		meta->oldpwd = ft_strdup(meta->pwd);
		free(meta->pwd);
		meta->pwd = ft_strdup(pwd);
		free(pwd);
	}
	else
	{
		builtin_error(dir, 72);
	}
}

void	cd_execute(t_data *meta, char *str)
{
	char	*dir;

	dir = get_cd_dir(meta, str);
	if (dir == NULL)
		return ;
	if (check_exec_stat(dir) == 0)
		return ;
	if (check_exec_permission(dir) == 0)
		return ;
	change_directory(meta, dir);
	free(dir);
}
