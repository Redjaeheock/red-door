/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_frist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:43 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/27 12:47:01 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	frist_export(t_data *meta)
{
	int		i;
	t_path	*temp;

	i = 1;
	sort_export(&meta->exp);
	temp = meta->exp;
	while (temp != NULL)
	{
		printf("declare -x %s\n", temp->set);
		temp = temp->next;
		i++;
	}
	printf("환경변수의 개수눈 = %d 입니다 \n", i);
}
