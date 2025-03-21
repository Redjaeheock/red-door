/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:30:28 by jahong            #+#    #+#             */
/*   Updated: 2025/01/22 15:33:15 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, const char *s2, unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (len < n && ((((unsigned char *)s1)[len] != '\0')
			|| (((unsigned char *)s2)[len] != '\0')))
	{
		if (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len] != 0)
			return (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len]);
		len++;
	}
	return (0);
}
