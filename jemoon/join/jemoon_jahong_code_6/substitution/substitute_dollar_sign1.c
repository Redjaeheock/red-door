/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:09:16 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:09:50 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_pass_substitute(char *str, char c)
{
	int		cnt;
	int		quote;

	quote = check_quote_pair(str[0], 0);
	if (quote == 1 && c == 'c')
		return (1);
	cnt = check_split_point_str(str);
	if (cnt == 0)
		return (1);
	return (0);
}

t_tmp	*search_n_change_dollar_sign(t_data *meta, char *str, char c)
{
	t_tmp	*tmp;
	int		result;

	result = check_pass_substitute(str, c);
	if (result == 1)
		return (pass_substitute(str));
	tmp = change_dollar_sign(meta, str);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

t_tmp	*do_substitute_dollar_sign(t_data *meta, char **str, char c)
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
		tmp->next = search_n_change_dollar_sign(meta, str[row], c);
		if (tmp->next == NULL)
			return (free_tmp_list(node));
		tmp = last_tmp_list(tmp);
		row++;
	}
	tmp = node;
	node = node->next;
	free(tmp);
	return (node);
}
