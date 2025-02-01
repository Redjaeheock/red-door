/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:56:37 by jahong            #+#    #+#             */
/*   Updated: 2025/02/01 16:20:33 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_quote_set_jump(char *s, char *tmp)
{
	int		quote;
	int		idx;
	int		n;

	quote = 0;
	idx = 0;
	n = 0;
	while (s[idx] != '\0')
	{
		quote = check_quote_pair(s[idx], quote);
		if ((s[idx] == '\'' && quote == 1) || (s[idx] == '"' && quote == 2) ||
			(quote == 0 && (s[idx] == '"' || s[idx] == '\'')))
		{
			idx++;
			continue ;
		}
		tmp[n] = s[idx];
		n++;
		idx++;
	}
	tmp[n] = '\0';
	return (tmp);
}

int	keep_quote_set(t_list *node, char c)
{

	if (node->token[0] == '"' && ft_strcmp(node->token, "\"\"") == 0)
	{
		if (node->key == NULL)
		{
			node->key = ft_strdup(node->token);
			if (node->key == NULL)
				return (0);
		}
	}
	else if (node->token[0] == '\'' && ft_strcmp(node->token, "''") == 0)
	{
		if (node->key == NULL)
		{
			node->key = ft_strdup(node->token);
			if (node->key == NULL)
				return (0);
		}
	}
	return (1);
}

int	remove_quote_tokens(t_list *node, char c)
{
	char	*str;
	int		len;

	len = quote_set_jump_len(node->token);
	printf("jump quote len = %d\n", len);
	if (len == 0 && node->token == NULL)
		return (1);
	if (keep_quote_set(node, c) == 0)
		return (0);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	str = copy_quote_set_jump(node->token, str);
	if (node->token != NULL)
		free(node->token);
	printf("after_remove_str = %s\n", str);
	node->token = str;
	return (1);
}
