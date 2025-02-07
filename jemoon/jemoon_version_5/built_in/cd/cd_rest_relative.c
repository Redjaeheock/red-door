/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest_relative.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:03:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 11:10:39 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

char	*get_relative_path(t_data *meta, char **sp_dir)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = ft_strdup(get_env(meta->exp, "PWD"));
	if (pwd == NULL)
		return (NULL);
	while (sp_dir[i] != NULL)
	{
		if (is_parent_dir(sp_dir[i]))
			pwd = back_path(pwd);
		else if (is_current_dir(sp_dir[i]))
		{
			i++;
			continue ;
		}
		else
			pwd = add_path(pwd, sp_dir[i]);
		i++;
	}
	return (pwd);
}
