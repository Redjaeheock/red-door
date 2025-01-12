/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitusion_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:43 by jahong            #+#    #+#             */
/*   Updated: 2025/01/12 18:27:04 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *change_envval(char *str)
{
	int	idx;
	int	len;
	int	quote;

	idx = 0;
	len = 0;
	quote = 0;
	while (str[idx] != '\0')
	{
		if (str[idx + len] == '\0' && quote == 0)
			

		
	}
}

char	*divede_token_str(char *token,  int row)
{
	char	**str;
	int		idx;
	int		quote;

	idx = 0;
	quote = 0;
	str = (char *)malloc(sizeof(char *) * (row + 1));
	if (str == NULL)
		return (sndry_alloc_err(NULL));
	while (idx <= row)
	{
		str[idx] = change_envval(token);
		if (str[idx] == NULL)
		{
			sndry_alloc_err((void **)str);
			return (NULL);
		}
		idx++;
	}
	return (str);
}

char	*ch_dollar_to_envval(char *token, int row)
{
	char 	**div_str;
	char 	*join_str;

	div_str = divede_token_str(token, row);
	join_str = join_token_str(div_str);

}

int	check_dollar_sign_invalid(char *s, int row)
{
	int		idx;
	int		quot;

	idx = 0;
	quot = 0;
	while (s[idx] != '\0')
	{
		if (quot == 0) 
		{
			if (s[idx] == '\'')
				quot = 1;
			else if (s[idx] == '"')
				quot = 2;
			else if (idx == 0 || s[idx - 1] == '\'' || s[idx - 1] == '"')
				row++;
		}
		else if ((quot == 1 && s[idx] == '\'') || (quot == 2 && s[idx] == '"')) 
		{
			quot = 0;
			row++;
		}
   	 	idx++;
	}
	return (row);
}
int	mapping_dollor_sign(char **token)
{
	char	*str;
	int		row;

	row = check_dollar_sign_invalid(*token, row = 0); //norm check!!!
	str = ch_dollar_to_envval(*token, row);
	
}
int	check_quote_invalid(char *token)
{
	int	idx;
	int quote;

	idx = 0;
	quote = 0;
	while (token[idx] != '\0')
	{
		if (token[idx] == '\'' && quote == 0)
			quote = 1;
		else if (token[idx] == '"' && quote == 0)
			quote = 2;
		else if (token[idx] == '\'' && quote == 1)
			quote = 0;
		else if (token[idx] == '"' && quote == 2)
			quote = 0;
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
		if (mapping_dollor_sign(&(tokens->token)) == 0);
			return (0);
		tokens = tokens->next;
	}
	return (1);
}