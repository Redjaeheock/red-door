/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_frist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/27 13:05:57 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	frist_export(t_data *meta)
{
	t_path	*temp;

	sort_export(&meta->exp);
	temp = meta->exp;
	while (temp != NULL)
	{
		printf("declare -x %s\n", temp->set);
		temp = temp->next;
	}
}
