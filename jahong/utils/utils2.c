/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:28:07 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 14:35:57 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *copy_index_range(char *str, int idx, int end)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = end - idx;
	if (end != ft_strlen(str))
		len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		tmp[i] = str[idx];
		idx++;
		i++;
	}
	tmp[i] = '\0';
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