/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/02/02 12:21:16 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_pattern(t_data *meta, t_list *node, char *str, int *idx)
{
	t_path	*tmp;
	char	*copy;
	int		start;

	tmp = meta->env;
	start = *idx;
	if (node->key != NULL)
	{
		while (node->key[*idx] != '\0')
		{
			if (ft_isalnum(node->key[*idx]) == 0 && node->key[*idx] != '_')
				break ;
			*idx += 1;
		}
	}
	// printf("idx = %d | chr = %c\n", *idx, str[*idx]);
	copy = copy_index_range(node->key, start, *idx);
	if (copy == NULL)
		return(NULL);
	printf("extract agter dollar string = %s\n", copy);
	while (tmp != NULL)
	{
		if (ft_strcmp(copy, tmp->key) == 0)
			break;
		tmp = tmp->next;
	}
	free(copy);
	copy = NULL;
	copy = ft_strjoin_v2(str, tmp->value);
	printf("extract agter dollar string21222 = %s\n", copy);
	return (copy);
}

char	*copy_next_dollar(t_data *meta, t_list *node, char *str, int *idx)
{
	char	*keep1;
	char	*keep2;
	int		start;

	keep2 = NULL;
	*idx += 1;
	start = *idx;
	if (node->key[*idx] == '$')
	{
		keep1 = copy_current_process_pid();
		if (keep1 == NULL)
			return (NULL);
		printf("keep1 = %s\n", keep1);
		keep2 = ft_strjoin_v2(str, keep1);
		free(keep1);
		if (keep2 == NULL)
			(NULL);
		*idx += 1;
	}
	else
		keep2 = ft_strdup(str);
	// else
	// {
	// 	while (node->key[*idx] != '\0')
	// 	{
	// 		if (ft_isalnum(node->key[*idx]) == 0 && node->key[*idx] != '_')
	// 			break ;
	// 		*idx += 1;
	// 	}
	// 	keep2 = copy_index_range(node->key, start, *idx);
	// 	if (keep2 == NULL)
	// 		return (NULL);
	// }
	printf("keep2 = %s\n", keep2);
	keep1 = make_pattern(meta, node, keep2, idx);
	if (keep2 != NULL)
		free(keep2);
	return (keep1);
}

char	*copy_before_dollar(t_list *node, char *str, int idx, int end)
{
	char	*copy;
	char	*keep;

	keep = NULL;
	copy = copy_index_range(node->key, idx, end);
	if (copy == NULL)
		return (NULL);
	printf("copy = %s\n", copy);
	keep = ft_strjoin_v2(str, copy);
	printf("keep = %s\n", keep);
	free(copy);
	return (keep);
}
char	*change_partial_envvar(t_data *meta, t_list *node, int idx, int end)
{
	char	*str;
	char	*keep;
	int		start;

	str = NULL;
	start = idx;
	printf("end idx = %d\n", end);
	while (idx <= end)
	{
		if (node->key[idx] == '$' || idx == end)
		{
			keep = copy_before_dollar(node, str, start, idx);
			if (str != NULL)
				free(str);
			if (keep == NULL)
				return (NULL);
			if (idx == end)
			{
				str = keep;
				break ;
			}
			str = copy_next_dollar(meta, node, keep, &idx);
			printf("key[%d] = %c\n", idx, node->key[idx]);
			printf("str = %s\n", str);
			start = idx;
			free(keep);
			if (str == NULL)
				return (NULL);
		}
		else
		{
			idx++;
			

		}
	}
	return (str);
}

char	*token_start_wildcard(t_data *meta, t_list *node, int idx)
{
	char	*str;
	int		start;
	int		flag;

	flag = 0;
	start = idx;
	if (node->key != NULL)
	{	
		while (node->key[idx] != '\0')
		{
			if (node->key[idx] == '"')
				flag = !(flag);
			if (node->key[idx] == '$' && flag == 0)
				break ;
			idx++;
		}
		printf("start = %d | idx = %d\n", start, idx);
		return (change_partial_envvar(meta, node, start, idx));		
	}
	// else
	// 	while (node->token[idx] != '$' && node->token[idx] != '\0')
	// 		idx++;
	// 	str = copy_index_range(node->token, start, idx);
	// 	retu
	return (0);
}
int	check_valid_wildcard(t_data *meta, t_list *node)
{
	char	*str;
	int		idx;
	int		result;

	idx = 0;
	result = 0;
	str = NULL;
	if (node->token != NULL && node->token[idx] == '*')
	{
		while (node->token[idx] == '*')
			idx++;
		if (node->token[idx] == '\0')
			return (change_only_wildcard_token(node));
		str = token_start_wildcard(meta, node, idx);
		printf("make patten string = %s\n", str);
		if (str == NULL)
			return (0);
		result = change_partial_wildcard1(node, str);
		free(str);
		//printf("remake check_valid_wlidcard f_list[0] = %s\n", node->f_list[0]);
	}
	return (result);
}
int	search_wildcard_in_token(t_list *node)
{
	int		cnt;
	int		valid;
	int		idx;
	int		quote;

	cnt = 0;
	valid = 1;
	idx = 0;
	quote = 0;
	while (node->token != NULL && node->token[idx] != '\0')
	{
		quote = check_quote_pair(node->token[idx], quote);
		if (node->token[idx] == '*' && quote == 0)
			cnt++;
		idx++;
	}
	if (cnt == 0)
		valid = 0;
	return (valid);
}
int	substitute_wildcard(t_data *meta, t_list *node)
{
	int		var;

	var = search_wildcard_in_token(node);
	printf("1 var = %d\n", var);
	if (var == 0)
		return (1);
	var = check_valid_wildcard(meta, node);
	if (var == -1)
		return (var);
	printf("after wildcard substitued key = %s\n", node->key);
	printf("after wildcard substitued token = %s\n", node->token);
	if (node->f_list != NULL)
		printf("after wildcard substitued f_list = %s\n", node->f_list[0]);



	
	return (var);
}
