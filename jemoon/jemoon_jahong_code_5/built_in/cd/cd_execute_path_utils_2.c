/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_path_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:01:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/05 17:37:36 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	get_slash_position(char *str, int slash_len, int *i, int *count_slash)
{
	int	j;
	int	str_len;

	j = 0;
	str_len = ft_strlen(str);
	while (*i + j < str_len)
	{
		if (str[*i + j] == '/')
		{
			(*count_slash)++;
			(*i)++;
			while (str[*i + j] == '/')
				j++;
			if (slash_len == *count_slash)
			{
				if (*i == 0)
					(*i)++;
				return (*i);
			}
		}
		else
			(*i)++;
	}
	return (*i);
}

void	make_back_path(char *pwd, char *back_path, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (pwd[i + j] == '/')
		{
			back_path[i] = pwd[i + j];
			i++;
			while (pwd[i + j] == '/')
				j++;
		}
		else
		{
			back_path[i] = pwd[i + j];
			i++;
		}
	}
	back_path[i] = '\0';
}
