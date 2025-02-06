/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:01:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/06 15:18:46 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	count_slash(char *str, char c)
{
	int	i;
	int	count;
	int	str_len;

	str_len = ft_strlen(str);
	i = 0;
	count = 0;
	while (i < str_len)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_back_path_len(char *str, int slash_len)
{
	int	i;
	int	str_len;
	int	count_slash;

	i = 0;
	str_len = ft_strlen(str);
	count_slash = 0;
	while (i < str_len)
	{
		if (str[i] == '/')
		{
			count_slash++;
			if (slash_len == count_slash)
				return (i);
		}
		i++;
	}
	return (i);
}

char	*remove_back_path(char *pwd, int len)
{
	char	*back_path;
	int		i;

	i = 0;
	back_path = (char *)malloc(sizeof(char) * (len + 1));
	if (back_path == NULL)
		return (NULL);
	while (i < len)
	{
		back_path[i] = pwd[i];
		i++;
	}
	back_path[i] = '\0';
	free(pwd);
	pwd = NULL;
	return (back_path);
}

char	*add_path(char *pwd, char *dir)
{
	return (ft_strjoin_front_slash(pwd, dir));
}

char	*back_path(char *pwd)
{
	int		slash_len;
	int		back_path_len;
	char	*back_path;

	slash_len = count_slash(pwd, '/');
	back_path_len = count_back_path_len(pwd, slash_len);
	back_path = remove_back_path(pwd, back_path_len);
	if (back_path == NULL)
		return (pwd);
	return (back_path);
}

