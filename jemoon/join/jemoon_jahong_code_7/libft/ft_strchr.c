/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:51:02 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 15:35:15 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			return (&((char *)s)[idx]);
		idx++;
	}
	if (s[idx] == c)
		return (&((char *)s)[idx]);
	return (NULL);
}
