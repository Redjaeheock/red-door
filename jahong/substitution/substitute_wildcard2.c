/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/21 23:17:32 by jahong           ###   ########.fr       */
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
	printf("remove wildcard\n");
	t_tmp	*head;
	t_tmp	*tmp;

	head = node->next;
	node->next = NULL;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free_single_tmp_node(tmp);
	}
	return (1);
}
int	check_remove_wildcard(t_tmp *node)
{
	t_tmp	*head;
	int		flag;

	head = node;
	flag = 1;
	while (node != NULL)
	{
		if (node->value != NULL)
		{
			flag = 0;
			break ;
		}
		if (node->key[0] != '*')
		{
			flag = 0;
			break;
		}
		node = node->next;
	}
	printf("whie is flag = %d\n", flag);
	return (flag);
	
}

int	check_valid_change_wildcard(t_tmp *node)
{
	int		cnt;
	int		cyc;
	int		result;

	cnt = 0;
	cyc = 0;
	result = 0;
	while (node != NULL)
	{
		cnt += are_all_characters_same(node->key, '*');
		node = node->next;
		cyc++;
	}
	if (cyc == cnt)
		result = 1;
	return (result);
}

int	change_all_node(t_tmp *node)
{
	t_tmp	*head;
	t_tmp	*tmp;

	head = node;
	node = node->next;
	head->next = NULL;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free_single_tmp_node(tmp);
	}
	free(head->key);
	head->key = change_wild_card();
	if (head ->key == NULL)
		return (0);
	return (1);
}

int	search_wildcard_all_node(t_tmp *node)
{
	int	cnt;

	cnt = 0;
	while (node != NULL)
	{
		cnt += are_all_characters_same(node->key, '*');
		node = node->next;
	}
	if (cnt == 0)
		return (0);
	return (1);
}

int	substitute_wildcard(t_tmp *node)
{
	t_tmp	*tmp;
	int		result;

	if (search_wildcard_all_node(node) != 1)
		return (1);
	if (check_valid_change_wildcard(node) == 1)
		return (change_all_node(node));
	printf("value = %s\n", node->value);
	if (node->value != NULL && check_remove_wildcard(node->next) == 1)
	{
		return (remove_wildcard_in_node(node));
	}

	return (1);
}
