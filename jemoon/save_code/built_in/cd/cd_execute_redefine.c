/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_excute_redefine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:00:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 17:41:44 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

char	*redefine_pwd(t_data *meta, char *dir)
{
	char	*pwd;
	char	**sp_dir;

	sp_dir = ft_split(dir, '/');
	if (sp_dir == NULL)
		return (NULL);
	if (is_absolute_path(dir) == 1)
		pwd = get_absolute_path(sp_dir);
	else
		pwd = get_relative_path(meta, sp_dir);
	free_double_string_array(sp_dir);
	return (pwd);
}

void	redefine_export(t_data *meta, t_path **exp, char *home)
{
	char	*pwd;
	t_path	*add_path;

	pwd = ft_strdup(meta->pwd);
	if (pwd == NULL)
		return ;
	if (find_node(*exp, "OLDPWD") == 0)
	{
		free(pwd);
		return ;
	}
	else
	{
		set_free_by_key(exp, "OLDPWD");
		set_value_by_key(exp, "OLDPWD", pwd);
		set_null_by_key(exp, "PWD");
		set_value_by_key(exp, "PWD", home);
	}
	free(pwd);
	return ;
}
