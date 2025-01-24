/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sub_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:45 by jahong            #+#    #+#             */
/*   Updated: 2025/01/24 21:10:59 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_null_string_n_null_point(t_list *tokens, char *str)
{
	if (tokens->key[0] == '$' && tokens->token[0] == '\0')
	{
		free(tokens->token);
		tokens->token = NULL;
	}
	else if (ft_strcmp(tokens->token, "\"\"") == 0)
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
// void	join_remove_wildcard(t_list *tokens, t_tmp *node)
// {
// 	t_tmp	*head;
// 	t_tmp	*tmp;

// 	head = node;
// 	while (head != NULL && (head->value == NULL || head->value[0] == '\0'))
// 		head = head->next;
// 	tmp = head->next;
// 	head->next = NULL;
// 	while (tmp != NULL)
// 	{
// 		head = tmp;
// 		tmp = tmp->next;
// 		free_single_tmp_node(head);
// 	}
// }

// int	check_remove_wildcard(t_tmp *node)
// {
// 	int		cnt;
// 	int		wildcard;

// 	cnt = 0;
// 	wildcard = 0;
// 	while (node != NULL)
// 	{
// 		if (cnt == 0 && are_all_characters_same(node->key, '*') == 1)
// 			wildcard++;
// 		if (node->value != NULL && node->value[0] != '\0')
// 			cnt++;
// 		if (cnt == 1  && 1 <= wildcard)
// 			return (0);
// 		if (1 < cnt)
// 			return (0);
// 		node = node->next;
// 	}
// 	if (cnt != 1)
// 		return (0);
// 	return (1);
// }
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
