/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 13:49:04 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	oldpwd_add(t_data *meta, t_path *export_add)
{
	if (ft_strcmp(export_add->key, "OLDPWD") == 0)
	{
		if (meta->oldpwd != NULL)
		{
			free(meta->oldpwd);
			meta->oldpwd = NULL;
		}
		meta->oldpwd = ft_strdup(export_add->value);
	}
}

int	is_invalid_number_start(char *str, int equal)
{
	if ('0' <= str[0] && str[0] <= '9')
	{
		builtin_error(str, 51);
		return (0);
	}
	return (1);
}

int	is_invalid_special_char(char *str, int equal)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < equal)
	{
		if (!(('A' <= str[i] && str[i] <= 'Z') || \
			('a' <= str[i] && str[i] <= 'z') || \
			('0' <= str[i] && str[i] <= '9') || \
			(str[i] == '_')))
		{
			builtin_error(str, 51);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_var_name(char *str, int equal)
{
	if (is_invalid_number_start(str, equal) == 0)
		return (0);
	if (is_invalid_special_char(str, equal) == 0)
		return (0);
	return (1);
}
