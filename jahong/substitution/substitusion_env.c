/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitusion_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:43 by jahong            #+#    #+#             */
/*   Updated: 2025/01/10 17:26:55 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	searching_word(t_list *tokens)
{
	int	idx;

	idx = 1;
	if (tokens->token[0] == '$' || tokens->token[0] == '"')
	{
		while (tokens->token[idx] != '\0')
		{
			
		}
	}
}
int	check_qoute(t_list *tokens)
{
	int	idx;
	int	sgle;
	int	dble;

	sgle = 0;
	dble = 0;
	while (tokens != NULL)
	{
		idx = 0;
		while (tokens->token[idx] != '\0')
		{
			if (tokens->token[idx] == '\'')
				sgle++;
			if (tokens->token[idx] == '"')
				dble++;
		}
		sgle = 0;
		dble = 0;
	}
}
int	substitution_dollar_sign(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (check_quote(tokens) == 0)
			return (0);
		searching_word(tokens);
		tokens = tokens->next;
	}
	return (1)
}