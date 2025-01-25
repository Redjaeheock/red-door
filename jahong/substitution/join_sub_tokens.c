/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sub_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:45 by jahong            #+#    #+#             */
/*   Updated: 2025/01/25 11:16:40 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_null_string_n_null_point(t_list *tokens, char *str)
{
	if (tokens->key[0] == '$' && str[0] == '\0')
	{
		free(tokens->token);
		tokens->token = NULL;
	}
	else if (ft_strcmp(str, "\"\"") == 0)
	{
		free(tokens->token);
		tokens->token = "";
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

char	*alloc_tokens_token(t_tmp *tmp)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	while (tmp != NULL)
	{
		if (tmp->value == NULL && tmp->key[0] != '$')
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
char	*alloc_tokens_key(t_tmp *tmp)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	while (tmp != NULL)
	{
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
int	join_sub_tokens(t_list *tokens, t_tmp *node)
{
	char	*str;
	
	str = alloc_tokens_key(node);
	if (str == NULL)
		return (0);
	if (tokens->key != NULL)
		free(tokens->key);
	tokens->key = str;
	str = alloc_tokens_token(node);
	if (str == NULL) 
		return (0);
	if (change_null_string_n_null_point(tokens, str) == 0)
		return ((free(str), 0));
	return ((free(str), 1));
}
