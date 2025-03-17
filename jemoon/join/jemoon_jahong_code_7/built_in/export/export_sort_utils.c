/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:01 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/07 19:33:06 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	ft_test(char *s1, const char *s2)
{
	unsigned int	len;

	len = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (((((unsigned char *)s1)[len] != '\0') \
	|| (((unsigned char *)s2)[len] != '\0')))
	{
		if (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len] != 0)
			return (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len]);
		len++;
	}
	return (0);
}
