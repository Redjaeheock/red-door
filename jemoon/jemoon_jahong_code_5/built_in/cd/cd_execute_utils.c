/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:00:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 17:47:07 by jemoon           ###   ########.fr       */
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

char	*set_dir(t_data *meta, char *str)
{
	char	*dir;

	if (ft_strcmp(str, "-") == 0)
	{
		dir = ft_strdup(meta->oldpwd);
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
