/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2_utils_3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:01:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/21 15:06:41 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	get_redefine_cmd_size(t_list *tokens, int cmd_size, \
		int *redefine_size, int *count_i)
{
	t_list	*temp;
	char	**str;
	int		i;

	i = 0;
	temp = tokens;
	while (i < cmd_size)
	{
		if (temp->key != NULL)
		{
			str = ft_split(temp->token, 32);
			*redefine_size = *redefine_size + sndry_arr_len((void **)str);
			free_sndry_arr((void **)str);
			str = NULL;
			(*count_i)++;
		}
		temp = temp->next;
		i++;
	}
}

int	redefine_cmd_size(t_list *tokens, int cmd_size)
{
	int		count_i;
	int		redefine_size;
	char	**str;

	redefine_size = 0;
	count_i = 0;
	get_redefine_cmd_size(tokens, cmd_size, &redefine_size, &count_i);
	if (redefine_size != 0)
		redefine_size = cmd_size - count_i + redefine_size;
	return (redefine_size);
}
