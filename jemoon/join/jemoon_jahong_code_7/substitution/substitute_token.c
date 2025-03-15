/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:09 by jahong            #+#    #+#             */
/*   Updated: 2025/03/15 17:38:51 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	measure_length_quote_set(char *str, int cnt)
{
	int	idx;
	int	qt;

	idx = 0;
	qt = 0;
	while (str[idx] != '\0')
	{
		if (qt == 0)
		{
			if (str[idx] == '\'')
				qt = 1;
			else if (str[idx] == '"')
				qt = 2;
			else if (idx == 0 || str[idx - 1] == '\'' || str[idx - 1] == '"')
				cnt++;
		}
		else if ((qt == 1 && str[idx] == '\'') || (qt == 2 && str[idx] == '"'))
		{
			qt = 0;
			cnt++;
		}
		idx++;
	}
	return (cnt);
}

int	subtitute_dollar_sign(t_data *meta, t_list *tokens, char c)
{
	t_tmp	*node;
	char	**tmp;
	int		var;

	if (search_chr_in_str(tokens->token, '$') == 0)
		return (1);
	var = measure_length_quote_set(tokens->token, var = 0);
	tmp = dividing_sub_token(tokens->token, var);
	if (tmp == NULL)
		return (0);
	node = do_substitute_dollar_sign(meta, tmp, c);
	free_sndry_arr((void **)tmp);
	if (node == NULL)
		return (0);
	var = join_sub_tokens(tokens, node, c);
	if (var == 0)
		return (0);
	free_tmp_list(node);
	return (1);
}

int	check_quote_valid(char *token)
{
	int	idx;
	int	quote;

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

int	substitute_tokens(t_data *meta, t_list *tokens, char c)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (c == 'c')
		{
			if (check_quote_valid(tmp->token) == 0)
				return (0);
		}
		/*
		if (subtitute_dollar_sign(meta, tmp, c) == 0)
			return (0);
		if (c == 'c')
		{
			if (substitute_wildcard(tmp) == -1)
				return (0);
			if (remove_quote_tokens(tmp) == 0)
				return (0);
		}
		*/
		tmp = tmp->next;
	}
	return (1);
}
