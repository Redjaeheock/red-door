/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:41:12 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 17:23:30 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	char_arr_len(char **array)
{
	int	len;

	len = 0;
	if (array == NULL)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}

int	ft_test(char *s1, const char *s2)
{
	unsigned int	len;

	len = 0;
	while (((((unsigned char *)s1)[len] != '\0') \
	|| (((unsigned char *)s2)[len] != '\0')))
	{
		if (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len] != 0)
			return (((unsigned char *)s1)[len] - ((unsigned char *)s2)[len]);
		len++;
	}
	return (0);
}
