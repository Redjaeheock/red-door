/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_check_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 20:13:42 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	is_valid_env_char(int c)
{
	if (('A' <= c && c <= 'Z') || \
		('a' <= c && c <= 'z') || \
		('0' <= c && c <= '9') || \
		(c == '_'))
		return (1);
	return (0);
}

int	search_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_invalid_number_start(char *str, int equal)
{
	if ('0' <= str[0] && str[0] <= '9')
	{
		builtin_error(str, 51);
		return (0);
	}
	if ('=' == str[0])
	{
		builtin_error(str, 51);
		return (0);
	}
	return (1);
}
