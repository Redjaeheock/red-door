/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest_absolute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:02:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 11:03:04 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	is_absolute_path(char *dir)
{
	if (dir == NULL)
		return (-1);
	if (dir[0] == '/')
		return (1);
	return (0);
}

char	*get_absolute_path(char **sp_dir)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = (char *)malloc(sizeof(char ) * 2);
	if (pwd == NULL)
		return (NULL);
	pwd[0] = '/';
	pwd[1] = '\0';
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
