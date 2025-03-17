/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute_path_utils_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:01:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/16 21:09:36 by jahong           ###   ########.fr       */
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
		{
			count++;
			while (str[i] == c)
				i++;
		}
		i++;
	}
	return (count);
}

int	count_back_path_len(char *str, int slash_len)
{
	int	i;
	int	count_slash;

	i = 0;
	count_slash = 0;
	return (get_slash_position(str, slash_len, &i, &count_slash));
}

char	*remove_back_path(char *pwd, int len)
{
	char	*back_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (len <= 0)
		len = 1;
	back_path = (char *)malloc(sizeof(char) * (len + 1));
	if (back_path == NULL)
		return (NULL);
	make_back_path(pwd, back_path, len);
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
	back_path = remove_back_path(pwd, back_path_len - 1);
	if (back_path == NULL)
		return (pwd);
	return (back_path);
}
