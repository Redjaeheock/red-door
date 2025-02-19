/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:55 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/19 17:55:20 by jemoon           ###   ########.fr       */
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
