/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:28:07 by jahong            #+#    #+#             */
/*   Updated: 2025/02/06 13:55:57 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**change_system_error_msg(void)
{
	char	**msg;

	msg = (char **)malloc(sizeof(char *) * 2);
	if (msg == NULL)
		return (memory_alloc_error());
	msg[0] = ft_strdup("Not valid path");
	msg[1] = NULL;
	return (msg);
}

char	*search_value_using_key(t_path *path, char *src)
{
	char *value;

	value = NULL;
	while (path != NULL)
	{
		if (ft_strcmp(path->key, src) == 0)
		{
			value = ft_strdup(path->value);
			if (value == NULL)
				return (memory_alloc_error());
			break ;
		}
		path = path->next;
	}
	return (value);
}

char	*copy_conditional_index_range(char *str, int idx, int end, char c)
{
	char	*tmp;
	int		n;
	int		len;

	n = 0;
	len = end - idx;
	if (end != ft_strlen(str))
		len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		if (str[idx] == c)
		{
			idx++;
			continue ;
		}
		tmp[n] = str[idx];
		idx++;
		n++;
	}
	tmp[n] = '\0';
	return (tmp);
}

char *copy_index_range(char *str, int idx, int end)
{
	char	*tmp;
	int		n;
	int		len;

	n = 0;
	len = end - idx;
	if (end != ft_strlen(str))
		len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		tmp[n] = str[idx];
		idx++;
		n++;
	}
	tmp[n] = '\0';
	return (tmp);
}

int	ck_part_of_special_chr(int c)
{
	if ('!' <= c && c <= '/')
		return (1);
	if (c == ':' || c == ';')
		return (1);
	if (c == '=' || c == '@')
		return (1);
	if ('[' <= c && c <= '^')
		return (1);
	if (c == '`' || ('{' <= c && c <= '~'))
		return (1);
	return (0);
}