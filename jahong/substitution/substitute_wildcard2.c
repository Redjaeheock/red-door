/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/25 21:53:21 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_wild_card(t_path *env, t_list *node, char *src)
{
	int				result;
	int				cnt;

	if (src == NULL)
	{
		cnt = count_list_current_directory(".");
		if (cnt < 1)
			return (cnt);
		result = open_n_read_filenames1(node, ".", cnt);
		return (result);
	}
	return (1);
}
int	check_valid_wlidcard(t_path *env, t_list *node)
{
	int	idx;
	int result;

	idx = 0;
	printf("node->key = %s\n", node->key);
	printf("node->token = %s\n", node->token);
	if (node->token[idx] == '*')
	{
		while (node->token[idx] == '*')
			idx++;
		if (idx == ft_strlen(node->token))
		{
			printf("all wildcard\n");
			return (change_wild_card(env, node, NULL));
		}
	}
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
	printf("after wildcard substitued key = %s\n", node->key);
	printf("after wildcard substitued token = %s\n", node->token);


	
	return (1);
}
