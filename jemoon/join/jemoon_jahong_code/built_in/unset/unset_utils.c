/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:42:16 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 18:39:15 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	search_special_characters_unset(char *str)
{
	int	i;

	i = 0;
	while (('0' <= str[i] && str[i] <= '9') && str[i] != '\0')
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			printf("bash: unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	while (str[i] != '\0')
	{
		if (!(('A' <= str[i] && str[i] <= 'Z') || \
		('a' <= str[i] && str[i] <= 'z') || \
		('0' <= str[i] && str[i] <= '9') || \
		(str[i] == '_')))
		{
			printf("bash: unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}
