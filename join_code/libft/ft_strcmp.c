/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:21:40 by jahong            #+#    #+#             */
/*   Updated: 2025/01/26 21:14:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	idx;
	int				s1_len;
	int				s2_len;

	s1_len = (int)ft_strlen((char *)s1);
	s2_len = (int)ft_strlen((char *)s2);
	if (s2 == NULL || s1_len > s2_len)
		return (1);
	else if (s1 == NULL || s1_len < s2_len)
		return (-1);
	idx = 0;
	while (((char *)s1)[idx] != '\0' && ((char *)s2)[idx] != '\0')
	{
		if (((unsigned char *)s1)[idx] > ((unsigned char *)s2)[idx])
			return (1);
		else if (((unsigned char *)s1)[idx] < ((unsigned char *)s2)[idx])
			return (-1);
		idx++;
	}
	return (0);
}
