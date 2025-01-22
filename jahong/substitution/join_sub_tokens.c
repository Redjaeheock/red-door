/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sub_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:45 by jahong            #+#    #+#             */
/*   Updated: 2025/01/22 14:48:35 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_splited_sub_token(t_tmp *tmp)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	while (tmp != NULL)
	{
		if (tmp->value == NULL)
			str2 = ft_strjoin_v2(str1, tmp->key);
		else
			str2 = ft_strjoin_v2(str1, tmp->value);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		tmp = tmp->next;
	}
	return (str1);
}
