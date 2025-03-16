/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:00:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 11:12:35 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	start_c(char *str, char c)
{
	if (str == NULL)
		return (0);
	if (str[0] == c)
		return (1);
	return (0);
}

int	is_current_dir(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i != 1)
		return (0);
	if (str[0] == '.' && str[1] == '\0')
		return (1);
	return (0);
}

int	is_parent_dir(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i != 2)
		return (0);
	if (str[0] == '.' && str[1] == '.' && str[2] == '\0')
		return (1);
	return (0);
}

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

char	*set_dir(t_data *meta, char *str)
{
	char	*dir;

	if (ft_strcmp(str, "-") == 0)
	{
		dir = search_value_using_key(meta->exp, "OLDPWD");
		if (dir == NULL)
		{
			printf("-bash: cd: OLDPWD not set\n");
			return (NULL);
		}
		printf("%s\n", dir);
		return (dir);
	}
	else if (ft_strcmp(str, "--") == 0)
		return (search_value_using_key(meta->exp, "HOME"));
	else if (ft_strcmp(str, "~") == 0)
		return (ft_strdup(meta->home));
	else if (start_c(str, '-') == 1 || start_c(str, '~') == 1)
	{
		printf("-bash: cd: %s: invalid option\n", str);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (NULL);
	}
	else
		return (ft_strdup(str));
}
