/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_n_div_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:59:11 by jahong            #+#    #+#             */
/*   Updated: 2025/01/16 16:03:01 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *copy_split_token(char *str, int idx, int end)
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
int	move_index(char *str, int idx, int num)
{
	if (num == 1)
	{
		while (str[idx] != '$' && str[idx] != '\0')
			idx++;
	}
	else
	{
		idx++;
		while (str[idx] != '\0')
		{
			if (str[idx] == '$')
			{
				idx++;
				break ;
			}
			else if (check_quote_pair(str[idx], 0) != 0 || str[idx] == ' ')
				break ;
			idx++;
		}
	}
	return (idx);
}
char	*split_token(char *str, int *idx)
{
	char	*tmp;
	int		start;

	start = *idx;
	if (str[*idx] != '$')
		*idx = move_index(str, *idx, 1);
	else
		*idx = move_index(str, *idx, 2);
	tmp = copy_split_token(str, start, *idx);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
char	**div_copy_token(char *str, int len)
{
	char	**tmp;
	int		row;
	int		idx;

	row = 0;
	idx = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (row < len)
	{
		tmp[row] = split_token(str, &idx);
		if (tmp[row] == NULL)
			return (sndry_alloc_err((void **)tmp));
		row++;
	}
	tmp[row] = NULL;
	return (tmp);
}