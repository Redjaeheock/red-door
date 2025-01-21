/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:09:16 by jahong            #+#    #+#             */
/*   Updated: 2025/01/21 12:23:56 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_null_string(t_tmp *node)
{
	t_tmp	*tmp;
	t_tmp	*keep;

	while (node != NULL)
	{
		keep = node;
		if (node->key[0] == '\0')
		{
			if (keep == node)
			{
				keep = NULL;
				tmp = node;
				node = node->next;
				if (tmp->key != NULL)
				{
					free(tmp->key);
					tmp->key = NULL;
				}
				if (tmp->value != NULL)
				{
					free(tmp->value);
					tmp->value = NULL;
				}
				free(tmp);
				tmp = NULL;
				keep = node;
			}
			else
			{
				while (keep != node && keep != NULL)
					keep = keep->next;
				tmp = node;
				node = node->next;
				if (keep != NULL)
					keep->next = node;
				if (tmp->key != NULL)
				{
					free(tmp->key);
					tmp->key = NULL;
				}
				if (tmp->value != NULL)
				{
					free(tmp->value);
					tmp->value = NULL;
				}
				free(tmp);
				tmp = NULL;
			}
		}
		node = node->next;
	}
	return ;
}
int	check_except_substitution(t_tmp	*node)
{
	int		len;

	len = ft_strlen(node->key);
	if (node->key[len - 1] == '$')
	{
		free(node->key);
		node->key = copy_current_process_pid();
		if (node->key == NULL)
			return (-1);
		return (1);
	}
	if (node->key[0] == '$' && node->key[1] == '?')
	{
		free(node->key);
		node->key = get_exit_no();
		if (node->key == NULL)
			return (-1);
		return (1);
	}
	return (0);
}

int	search_in_envpath(t_data *meta, t_tmp	*node)
{
	t_path	*tmp;
	int		result;

	tmp = meta->env;
	result = check_except_substitution(node);
	if (result != 0)
		return (result);
	while (tmp != NULL)
	{
		if (ft_strcmp(&node->key[1], tmp->key) == 0)
		{
			node->value = "1";
			node->value =  ft_strdup(tmp->value);
			if (node->value == NULL)
				return (-1);
		}
		tmp = tmp->next;
	}
	if (node->value == NULL)
	{
		node->key = change_null_string();
		if (node->key == NULL)
			return (-1);
	}
	return (1);
}
int	mapping_dollar_sign_to_env(t_data *meta, t_tmp *node)
{
	t_tmp	*tmp;
	int		result;

	tmp = node;
	while (tmp != NULL)
	{
		if (search_chr_in_str(tmp->key, '$') == 1 && ft_strlen(tmp->key) > 1)
		{
			result = search_in_envpath(meta, tmp);
			if (result == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}
t_tmp	*change_dollar_sign(t_data *meta, char *str)
{
	t_tmp	*tmp;
	t_tmp	*node;
	int		result;
	int		quote;
	int cnt = 0;

	quote = check_quote_pair(str[0], 0);
	tmp = dividing_copied_token(str, quote);
	if (tmp == NULL)
		return (NULL);
	node = tmp;
	while (node != NULL)
	{
		printf("list key = %s\n", node->key);
		printf("list value = %s\n", node->value);
		node = node->next;
	}
	printf("\n");
	result = mapping_dollar_sign_to_env(meta, tmp);
	if (result == -1)
		return (free_tmp_list(tmp));
	return (tmp);
}
int	check_split_point_str(char *str)
{
	int		cnt;
	int		idx;
	int		flag;

	cnt = 0;
	idx = 0;
	flag = 2;
	while (str[idx] != '\0')
	{
		if (str[idx] != '$' && flag == 2)
		{
			cnt++;
			flag = 0;
		}	
		else if (str[idx] == '$')
		{
			cnt++;
			flag = 1;
			if (str[idx + 1] == '$' || check_valid_back(str, idx + 1) != 0)
			{
				idx++;	
				flag = 2;
			}
		}
		else if (flag == 1)
		{
			if (check_quote_pair(str[idx], 0) != 0)
				cnt++;
			else if (str[idx] == ' ' || ck_part_of_special_chr(str[idx]) != 0)
			{
				cnt++;
				flag = 0;
			}
			else if (check_valid_back(str, idx) != 0)
			{
				cnt++;
				flag = 2;
			}
		}
		idx++;
	}
	return (cnt);
	// 줄 수 조정
}
t_tmp	*pass_substitute(char *str)
{
	t_tmp	*tmp;

	tmp = create_new_tmp_list(NULL, NULL);
	if (tmp == NULL)
		return (memory_alloc_error());
	tmp->key = ft_strdup(str);
	if (tmp->key == NULL)
		return (memory_alloc_error());
	return (tmp);
}

int	check_pass_substitute(char *str)
{
	int		cnt;
	int		quote;

	quote = check_quote_pair(str[0], 0);
	if (quote == 1)
		return (1);
	cnt = check_split_point_str(str);
	printf("cnt =========================== %d\n", cnt);
	if (cnt == 0)
		return (1);
	return (0);
}
t_tmp	*search_n_change_dollar_sign(t_data *meta, char *str)
{
	t_tmp	*tmp;
	t_tmp	*node;
	int		result;

	result = check_pass_substitute(str);
	if (result == 1)
		return (pass_substitute(str));
	tmp = change_dollar_sign(meta, str);
	if (tmp == NULL)
		return (NULL);
	node = tmp;
	while (node != NULL)
	{
		printf("return func after list key = %s\n", node->key);
		printf("return funcafter list value = %s\n", node->value);
		node = node->next;
	}
	return (tmp);
}
t_tmp	*substitute_dollar_sign(t_data *meta, char **str)
{
	t_tmp	*node;
	t_tmp	*tmp;
	int		row;

	row = 0;
	node = create_new_tmp_list(NULL, NULL);
	if (node == NULL)
		return (memory_alloc_error());
	tmp = node;
	while (str[row] != NULL)
	{
		tmp->next =  search_n_change_dollar_sign(meta, str[row]);
		if (tmp->next == NULL)
			return (free_tmp_list(node));
		tmp = last_tmp_list(tmp);
		row++;
	}
	remove_null_string(node->next);
	tmp = node;
	node = node->next;
	free(tmp);
	tmp = node;
	while (tmp != NULL)
	{
		printf("after remove token key = %s\n", tmp->key);
		printf("after remove token value = %s\n", tmp->value);
		tmp = tmp->next;
	}
	return (node);
}
