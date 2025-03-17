/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/11 14:56:48 by jemoon           ###   ########.fr       */
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
	int	i;

	i = 0;
	while (('0' <= str[i] && str[i] <= '9') && \
	(i < equal && str[i] != '\0'))
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			builtin_error(str, 51);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_invalid_special_char(char *str, int equal)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < equal)
	{
		if ((33 <= str[i] && str[i] <= 47) || \
		(58 <= str[i] && str[i] <= 64) || \
		(91 <= str[i] && str[i] <= 94) || \
		(123 <= str[i] && str[i] <= 126) || \
		(str[i] == 96))
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
