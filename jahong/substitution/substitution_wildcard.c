/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_wildcard.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/18 19:27:49 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	substitution_wildcard(char **str, int quote, int flag)
{
	char	*tmp;
	int		row;

	row = 0;
	if (check_wild_card(str) == 0)
		return (0);
	while (str[row] != NULL)
	{
		tmp = change_whild_card(str[row]);
		if (tmp == NULL)
			return ((sndry_alloc_err(NULL), -1));
		row++;
	}
	return (1);
}