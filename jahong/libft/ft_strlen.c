/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:34:29 by jahong            #+#    #+#             */
/*   Updated: 2025/01/27 09:49:12 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}
int	conditional_strlen(const char *s, unsigned char condition)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while ((s[len] != condition) && (s[len] != '\0'))
		len++;
	return (len);
}

int	conditional_jump_len(const char *s, unsigned char condition)
{
	int	idx;
	int	len;

	idx = 0;
	len = 0;
	if (s == NULL)
		return (0);
	while (s[idx] != '\0')
	{
		if (s[idx] == condition)
			len++;
		idx++;
	}
	return (len);
}