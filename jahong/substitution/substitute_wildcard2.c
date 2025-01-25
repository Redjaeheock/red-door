/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/25 10:00:26 by jahong           ###   ########.fr       */
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

int	remove_wildcard(t_list *single_token)
{
	char	*str;
	int		idx;

	idx = ft_strlen(single_token->token);
	idx--;
	while (single_token->token[idx] == '*')
		idx--;
	printf("idx = %d\n", idx);
	str = copy_index_range(single_token->token, 0, idx + 1);
	if (str == NULL)
		return (0);
	free(single_token->token);
	single_token->token = str;
	return (1);
}
int	check_remove_wildcard(t_data *meta, t_list *single_token)
{
	t_path	*tmp;
	char	*str;
	int		start;
	int		idx;
	int		quote;
	int		flag;
	int		cnt;

	tmp = meta->env;
	start = 0;
	idx = start;
	quote = 0;
	flag = 0;
	cnt = 0;
	while (single_token->key[idx] != '\0')
	{
		if (single_token->key[idx] == '$' && flag == 0)
		{
			flag = 1;
			start = idx;
		}
		else if (single_token->key[idx] == '$' && flag == 1)
		{
			flag = 0;
			str = copy_index_range(single_token->key, start, idx);
			while (tmp != NULL)
			{
				if (ft_strcmp(&str[1], tmp->key) == 0)
					cnt++;
				if (2 <= cnt)
					return (0);
				tmp = tmp->next;
			}
		}
		idx++;
	}

}
int	check_valid_substitute_wildcard(t_list *single_token)
{
	int	idx;
	int	len;
	int	flag;

	idx = 0;
	len = ft_strlen(single_token->token);
	if (len == 0 || (len == 1 && single_token->token[idx] != '*'))
		return (0);
	flag = 1;
	while (single_token->token[idx] == '*' && single_token->token[idx] != '\0')
		idx++;
	if (idx == 0)
		flag = 0;
	if (idx == len)
		return (1);
	idx = len;
	idx--;
	while (0 < idx && single_token->token[idx] == '*')
		idx--;
	printf("len = %d : idx = %d\n", len, idx);
	if (flag == 0 && idx != len - 1)
		return (2);
	return (0);
}
int	search_wildcard_in_token(t_list *single_token)
{
	int		cnt;
	int		valid;
	int		idx;

	cnt = 0;
	valid = 1;
	idx = 0;
	while (single_token->token != NULL && single_token->token[idx] != '\0')
	{
		if (single_token->token[idx] == '*')
			cnt++;
		idx++;
	}	
	if (cnt == 0)
		valid = 0;
	return (valid);
}
int	substitute_wildcard(t_data *meta, t_list *single_token)
{
	t_list	*tmp;
	int		var;

	tmp = single_token;
	var = search_wildcard_in_token(single_token);
	printf("1 var = %d\n", var);
	if (var == 0)
		return (1);
	var = check_valid_substitute_wildcard(single_token);
	printf("2 var = %d\n", var);
	if (var == 0)
		return (1);
	if (var == 1)
	{
		free(single_token->token);
		single_token->token == change_wild_card(meta);
		if (single_token->token == NULL)
			return (0);
		return (1);
	}
	if (var == 2)
	{
		var = check_remove_wildcard(meta, single_token);
		if (var != 0)
			return (remove_wildcard(single_token));
	}
	tmp = single_token;
	while (tmp != NULL)
	{
		printf("subsituted whildcard key = %s\n", tmp->key);
		printf("subsituted whildcard token = %s\n", tmp->token);
		tmp = tmp->next;
	}
	
	return (1);
}
