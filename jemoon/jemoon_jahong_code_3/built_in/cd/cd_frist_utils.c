/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_frist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:07:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/22 18:25:21 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	set_null_by_key(t_path **exp, char *key)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp((temp)->key, key) == 0)
		{
			free(temp->value);
			temp->value = NULL;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_value_by_key(t_path **exp, char *key, char *value)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			temp->value = ft_strdup(value);
			free(temp->set);
			temp->set = NULL;
			temp->set = ft_strjoin_v2(temp->key, "=");
			temp->set = ft_strjoin(temp->set, temp->value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_free_by_key(t_path **exp, char *key)
{
	t_path	*temp;

	temp = *exp;
	while (temp)
	{
		if (ft_strcmp((temp)->key, key) == 0)
		{
			if (temp->value != NULL)
			{
				free(temp->value);
				temp->value = NULL;
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_oldpwd(t_path *temp, char *str)
{
	char	*key;
	int		key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(str);
	key = (char *)malloc(sizeof(char) * (key_len + 1));
	if (key == NULL)
		return (-1);
	while (i < key_len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	temp->key = key;
	return (0);
}

void	redefine_export(t_path	**exp, char *home)
{
	char	*pwd;
	t_path	*add_path;

	pwd = get_env(*exp, "PWD");
	if (find_node(*exp, "OLDPWD") == 0)
		return ;
	else
	{
		set_free_by_key(exp, "OLDPWD");
		set_value_by_key(exp, "OLDPWD", pwd);
		set_null_by_key(exp, "PWD");
		set_value_by_key(exp, "PWD", home);
	}
	return ;
}
