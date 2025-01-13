/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitusion_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:43 by jahong            #+#    #+#             */
/*   Updated: 2025/01/13 17:11:54 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ch_dollar_to_envval(char *token, int dollar, int qoute)
{
	int	idx;

	idx = 0;


}

void	check_dollar_sign_invalid(char *s, int *dollars, int dollars_len)
{
	int	idx;
	int	quote;
	int dollars_idx;

	idx = 0;
	quote = 0;
	dollars_idx = 0;
	while (s[idx] != '\0')
	{
		quote = check_quote_pair(s[idx], quote);
		if (s[idx] == '$' && dollars_idx < dollars_len)
		{
			dollars[dollars_idx] = quote;
			dollars_idx++;
			if (s[idx + 1] == '$')
				idx++;
		}
   	 	idx++;
	}
}
int	count_dollar_sign(char *str)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '$')
		{
			cnt++;
			if (str[idx + 1] == '$')
				idx++;
		}
		idx++;
	}
	return (cnt);
}
int	mapping_dollor_sign(t_list *tokens)
{
	int	*dollars;
	int		quote;
	int		len;

	len = count_dollar_sign(tokens->token);
	dollars = malloc(sizeof(int) * len);
	if (dollars == NULL)
		return (0);
	check_dollar_sign_invalid(tokens->token, dollars, len);
	// if (dollar_flag == 1 && quote != 1)
	// 	str = ch_dollar_to_envval(tokens->token, dollar_idx, quote);
	// else
	// 	str = cp_dollar_to_toekn(tokens->token);
	return (0);
	
}
int	check_quote_invalid(char *token)
{
	int	idx;
	int quote;

	idx = 0;
	quote = 0;
	while (token[idx] != '\0')
	{
		quote = check_quote_pair(token[idx], quote);
		idx++;
	}
	if (quote != 0)
	{
		error_qoute(quote);
		return (0);
	}
	return (1);
}
int	substitution_env_var(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (check_quote_invalid(tokens->token) == 0)
			return (0);
		if (mapping_dollor_sign(tokens) == 0);
			return (0);
		tokens = tokens->next;
	}
	return (1);
}