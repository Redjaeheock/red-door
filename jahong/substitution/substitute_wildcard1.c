/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/29 08:08:18 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_start_wildcard(t_list *node, int idx)
{
	int	start;
	int	flag;

	flag = 0;
	start = idx;
	if (node->key != NULL)
	{	
		while (node->key[idx] != '$' && node->token[idx] != '\0')
		{
			if (node->key[idx] == '"')
			{
				flag++;
				if (flag % 2 == 0 && node->key[idx + 1] == '&')
					break ;
			}
			idx++;
		}	
	}
	else
		while (node->token[idx] != '$' && node->token[idx] != '\0')
			idx++;
	if (start != idx)
		return (change_partial_wildcard1(node, start, idx));	
	return (0);
}

int	check_valid_wlidcard(t_path *env, t_list *node)
{
	int	idx;
	int result;

	idx = 0;
	if (node->token != NULL && node->token[idx] == '*')
	{
		while (node->token[idx] == '*')
			idx++;
		if (node->token[idx] == '\0')
			return (change_only_wildcard_token(node));
		result = token_start_wildcard(node, idx);
		return (result);
	}
	return (0);
}
int	search_wildcard_in_token(t_list *node)
{
	int		cnt;
	int		valid;
	int		idx;

	cnt = 0;
	valid = 1;
	idx = 0;
	while (node->token != NULL && node->token[idx] != '\0')
	{
		if (node->token[idx] == '*')
			cnt++;
		idx++;
	}
	if (cnt == 0)
		valid = 0;
	return (valid);
}
int	substitute_wildcard(t_data *meta, t_list *node)
{
	t_list	*tmp;
	int		var;

	tmp = node;
	var = search_wildcard_in_token(node);
	printf("1 var = %d\n", var);
	if (var == 0)
		return (1);
	var = check_valid_wlidcard(meta->env, node);
	if (var == -1)
		return (var);
	printf("after wildcard substitued key = %s\n", node->key);
	printf("after wildcard substitued token = %s\n", node->token);
	if (node->f_list != NULL)
		printf("after wildcard substitued f_list = %s\n", node->f_list[0]);



	
	return (var);
}
