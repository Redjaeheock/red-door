/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_name_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 20:30:23 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	check_valid_characters(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_valid_env_char(str[i]) == 0)
		{
			builtin_error(str, 51);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_valid_characters_before_equal(char *str, int equal)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < equal)
	{
		if (is_valid_env_char(str[i]) == 0)
		{
			if (str[i] == '+' && i == equal - 1)
				return (2);
			builtin_error(str, 51);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_invalid_special_char(char *str, int equal)
{
	if (equal == 0)
		return (check_valid_characters(str));
	return (check_valid_characters_before_equal(str, equal));
}

int	is_valid_var_name(char *str, int equal)
{
	int	plus_check;

	if (is_invalid_number_start(str, equal) == 0)
		return (0);
	plus_check = is_invalid_special_char(str, equal);
	if (plus_check == 0)
		return (0);
	else if (plus_check == 2)
		return (2);
	return (1);
}

int	search_special_characters(char *str, int equal)
{
	int	plus_check;

	plus_check = is_valid_var_name(str, equal);
	if (plus_check == 0)
		return (0);
	return (plus_check);
}
