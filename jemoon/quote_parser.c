/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:36:58 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/12 14:48:13 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsor(char const *str, int *start_index, int *index)
{
	int	plag_quote_d;
	int	plag_quote_s;

	plag_quote_d = 0;
	plag_quote_s = 0;
	while (str[*index])
	{
		if (plag_quote_s == 0 && str[*index] == '\"')
		{
			(*index)++;
			plag_quote_d = 1;
		}
		else if (plag_quote_d == 0 && str[*index] == '\'')
		{
			(*index)++;
			plag_quote_s = 1;
		}
		else if (str[*index] == '|')
			return ;
		else if (str[*index] == '\"' && plag_quote_d == 1)
			return ;
		else if (str[*index] == '\'' && plag_quote_s == 1)
			return ;
		else if (str[*index] == '<' || str[*index] == '>')
			return ;
		else if (str[*index] == 32 && (plag_quote_d == 1 || plag_quote_s == 1))
		{
			(*index)++;
			continue ;
		}
		else if (str[*index] == 32)
			return ;
		else
			(*index)++;
	}
}
