/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_rest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:04:54 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/06 18:51:16 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

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

int	start_c(char *str, char c)
{
	if (str == NULL)
		return (0);
	if (str[0] == c)
		return (1);
	return (0);
}

char	*set_dir(t_data *meta, char *str)
{
	char *dir;

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
	else if (start_c(str, '-') == 1)
	{
		printf("-bash: cd: %s: invalid option\n", str);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (NULL);
	}
	else if (start_c(str, '~') == 1)
	{
		printf("-bash: cd: %s: invalid option\n", str);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (NULL);
	}
	else
		return (ft_strdup(str));
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
		free(pwd);
		pwd = NULL;
	}
	else
		printf("bash: cd:%s not set\n", dir);
	free(dir);
}
