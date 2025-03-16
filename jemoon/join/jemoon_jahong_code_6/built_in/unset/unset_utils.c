/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:42:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/14 15:35:28 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	search_special_characters_unset(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	if ('0' <= str[0] && str[0] <= '9')
	{
		builtin_error(str, 61);
		return (0);
	}
	while (str[i])
	{
		if (!(('A' <= str[i] && str[i] <= 'Z') || \
			('a' <= str[i] && str[i] <= 'z') || \
			('0' <= str[i] && str[i] <= '9') || \
			(str[i] == '_')))
		{
			builtin_error(str, 61);
			return (0);
		}
		i++;
	}
	return (1);
}
