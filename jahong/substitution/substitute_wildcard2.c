/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/24 21:10:37 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_wild_card(t_data *meta)
{
	char	*tmp;
	char	*wild_card;
	int		len;
	int		idx;

	idx = 0;
	wild_card = "file file 42 test path";
	len = ft_strlen(wild_card);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (memory_alloc_error());
	while (wild_card[idx] != '\0')
	{
		tmp[idx] = wild_card[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}

int	remove_wildcard_in_node(t_list *node)
{
	char	*str;
	int		idx;

	idx = 0;
	while (node->token[idx] != '\0')
	{
		if (node->token[idx] == '*')
			break ;
		idx++;
	}
	str = copy_index_range(node->token, 0, idx);
	if (str == NULL)
		return (0);
	free(node->token);
	node->token = str;
	return (1);
}
int	check_remove_wildcard(t_data *meta, t_list *tokens)
{
	t_list	*tmp;
	int		wildcard;
	int		flag;
	int		idx;

	tmp = tokens;
	while (tmp != NULL)
	{
		wildcard = 1;
		flag = 0;
		idx = 0;
		while (tmp->token != NULL && tmp->token[idx] != '\0')
		{
			if (wildcard == 1 && tmp->token[idx] == '*')
				flag = 1;
			if (tmp->token[idx] != '*')
				wildcard = 0;
			if (wildcard == 0 && tmp->token[idx] == '*')
			{
				if (flag == 0)
					flag = 2;
				else if (flag == 1)
					flag = 3;
			}
			idx++;
		}
		if (flag == 1 && wildcard == 1)
		{
			if (tokens->token != NULL)
			{
				free(tokens->token);
				tokens->token = change_wild_card(meta);
				if (tokens->token != NULL)
					return (0);
			}
		}
		else if (flag == 3)
			remove_wildcard_in_node(tmp);
		tmp = tmp->next;
	}
	return (1);
}
int	check_valid_wildcard_in_tokens(t_list *tokens)
{
	int		cnt;
	int		valid;

	cnt = 0;
	valid = 1;
	while (tokens != NULL)
	{
		if (tokens->token != NULL)
			cnt += search_chr_in_str(tokens->key, '*');
		tokens = tokens->next;
	}	
	if (cnt == 0)
		valid = 0;
	return (valid);
}
int	substitute_wildcard(t_data *meta, t_list *tokens)
{
	t_list	*tmp;
	int		var;

	tmp = tokens;
	var = check_valid_wildcard_in_tokens(tokens);
	printf("1 var = %d\n", var);
	if (var == 0)
		return (0);
	var = check_remove_wildcard(meta, tokens);
	printf("2 var = %d\n", var);
	if (var == 0)
		return (0);
	tmp = tokens;
	while (tmp != NULL)
	{
		printf("subsituted whildcard key = %s\n", tmp->key);
		printf("subsituted whildcard token = %s\n", tmp->token);
		tmp = tmp->next;
	}
	
	return (1);
}
