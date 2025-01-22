/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/22 22:13:59 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	measure_length_quote_set(char *str, int cnt)
{
	int	idx;
	int qt;

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
int	subtitute_dollar_sign_n_wlidcard(t_data *meta, t_list *tokens)
{
	t_tmp	*node;
	char	**tmp;
	char	*str;
	int		var;
	t_tmp	*test;

	if (search_chr_in_str(tokens->token, '$') == 0)
		return (1);
	var = measure_length_quote_set(tokens->token, var = 0);
	tmp = dividing_sub_token(tokens->token, var);
	if (tmp == NULL)
		return (0);
	node = substitute_dollar_sign(meta, tmp);
	test = node;
	while (test != NULL)
	{
		printf("reset substitue key = %s\n", test->key);
		printf("reset substitue value = %s\n", test->value);
		test = test->next;
	}
	printf("\n");
	free_sndry_arr((void **)tmp);
	if (node == NULL)
		return (0);
	var = substitute_wildcard(node);
	if (var == 0)
		return (0);
	test = node;
	while (test != NULL)
	{
		printf("reset substitue wc key = %s\n", test->key);
		printf("reset substitue wc value = %s\n", test->value);
		test = test->next;
	}
	str = join_splited_sub_token(node);
	if (str == NULL)
		return (0);
	free(tokens->token);
	tokens->token = str;
	return (1);
}
int	check_quote_valid(char *token)
{
	int	idx;
	int quote;
	int	cnt;

	idx = 0;
	quote = 0;
	cnt = 0;
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
int	substitute_tokens(t_data *meta, t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tokens != NULL)
	{
		if (check_quote_valid(tokens->token) == 0)
			return (0);
		if (subtitute_dollar_sign_n_wlidcard(meta, tokens) == 0)
			return (0);
		printf("after substitued token = %s\n", tokens->token);
		tokens = tokens->next;
	}
	return (1);
}