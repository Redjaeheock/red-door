/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sub_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:45 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:44:32 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_null_string_n_null_point(t_list *tokens, char *str, char c)
{
	if (tokens->key[0] == '$' && str[0] == '\0')
	{
		free(tokens->token);
		tokens->token = NULL;
	}
	else if (ft_strcmp(str, "\"\"") == 0)
	{
		free(tokens->token);
		tokens->token = change_null_string();
		if (tokens->token == NULL)
			return (0);
	}
	else if (tokens->token != NULL)
	{
		free(tokens->token);
		tokens->token = ft_strdup(str);
		if (tokens->token == NULL)
			return ((memory_alloc_error(), 0));
	}
	return (1);
}

int	conditional_jump_t_tmp(t_tmp **tmp, int flag, int quote)
{
	if (flag != 1 && (*tmp)->value == NULL && (*tmp)->key[0] == '$')
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	else if ((*tmp)->key != NULL && (*tmp)->key[0] == '$')
	{
		if ((quote == 0 && ft_strlen((*tmp)->key) == 1) && (*tmp)->next != NULL)
		{
			(*tmp) = (*tmp)->next;
			return (1);
		}
	}
	return (0);
}

char	*alloc_tokens_token(t_tmp *tmp, char c)
{
	char	*str1;
	char	*str2;
	int		quote;

	str1 = NULL;
	quote = 0;
	while (tmp != NULL)
	{
		if (tmp->key != NULL && tmp->key[0] == '"')
			quote = check_quote_pair(tmp->key[0], quote);
		if (tmp->value == NULL && tmp->key[0] != '$')
			str2 = ft_strjoin_v2(str1, tmp->key);
		else if (c == 'c' && conditional_jump_t_tmp(&tmp, 1, quote) == 1)
			continue ;
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

char	*alloc_tokens_key(t_tmp *tmp, char c)
{
	char	*str1;
	char	*str2;
	int		flag;
	int		quote;

	str1 = NULL;
	quote = 0;
	flag = is_token_all_null_after_join(tmp);
	while (tmp != NULL)
	{
		if (tmp->key != NULL && tmp->key[0] == '"')
			quote = check_quote_pair(tmp->key[0], quote);
		if (c == 'c' && conditional_jump_t_tmp(&tmp, flag, quote) == 1)
			continue ;
		str2 = ft_strjoin_v2(str1, tmp->key);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		tmp = tmp->next;
	}
	return (str1);
}

int	join_sub_tokens(t_list *tokens, t_tmp *node, char c)
{
	char	*str;

	str = alloc_tokens_key(node, c);
	if (str == NULL)
		return (0);
	if (tokens->key != NULL)
		free(tokens->key);
	tokens->key = str;
	str = alloc_tokens_token(node, c);
	if (str == NULL)
		return (0);
	if (change_null_string_n_null_point(tokens, str, c) == 0)
		return ((free(str), 0));
	return ((free(str), 1));
}
