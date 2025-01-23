/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/23 15:08:56 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_wild_card()
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

int	remove_wildcard_in_node(t_tmp *node)
{
	t_tmp	*head;
	t_tmp	*tmp;

	head = node;
	while (head->value == NULL && head->value[0] == '\0')
		head = head->next;
	tmp = head->next;
	head->next = NULL;
	while (tmp != NULL)
	{
		head = tmp;
		tmp = tmp->next;
		free_single_tmp_node(head);
	}
	return (1);
}
int	check_remove_wildcard(t_tmp *node)
{
	t_tmp	*head;
	t_tmp	*tmp;
	int		flag;

	head = node;
	tmp = node;
	flag = 1;
	while (tmp->value == NULL || tmp->value[0] == '\0')
		tmp = tmp->next;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->value != NULL && tmp->value[0] != '\0')
		{
			flag = 0;
			break ;
		}
		if (tmp->key[0] != '$' && tmp->key[0] != '*')
		{
			flag = 0;
			break;
		}
		tmp = tmp->next;
	}
	return (flag);
}
int	check_valid_wildcard_in_nodes(t_tmp *node)
{
	int		cnt;
	int		result;

	cnt = 0;
	result = 0;
	while (node != NULL)
	{
		cnt += are_all_characters_same(node->key, '*');
		node = node->next;
	}	
	if (cnt == 0)
		result = 0;
	return (result);
}
int	substitute_wildcard(t_tmp *node)
{
	int		cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt += are_all_characters_same(node->key, '*');
		node = node->next;
	}
	if (cnt == 0)
		return (1);
	return (1);
}
