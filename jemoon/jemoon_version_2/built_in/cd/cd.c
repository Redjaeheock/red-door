/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:32:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/31 15:13:30 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(t_path *env, char *home)
{
	t_path	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, home) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	redefine_export(t_path	**exp, char *home)
{
}

void	cd_home(t_data *meta)
{
	char	*home;

	home = get_env(meta->env, "home");
	if (home == NULL)
	{
		printf("bash: cd:HOME not set\n");
		return ;
	}
	if (chdir(home) == 0)
	{
		redefine_export();
		redefine_env();
	}
	else
		printf("bash: cd:%s not set\n", home);
}

void	minishell_cd(t_data *meta)
{
	int	export_len;

	if (ft_strcmp(meta->exec_cmd->str[0], "cd") != 0)
		return ;
	export_len = char_arr_len(meta->exec_cmd->str);
	if (export_len > 1)
	{
		cd_home(meta);
	}
}
