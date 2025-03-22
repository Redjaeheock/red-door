/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:09 by jahong            #+#    #+#             */
/*   Updated: 2025/03/22 15:30:18 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	measure_length_quote_set(char *str, int cnt, char c)
{
	int	idx;
	int	qt;

	idx = 0;
	qt = 0;
	while (str[idx] != '\0')
	{
		if (qt == 0)
		{
			if (str[idx] == '\'' || str[idx] == '"')
				qt = check_quote_pair(str[idx], qt);
			else if (idx == 0 || str[idx - 1] == '\'' || str[idx - 1] == '"')
				cnt++;
		}
		else if ((qt == 1 && str[idx] == '\'') || (qt == 2 && str[idx] == '"'))
		{
			qt = 0;
			cnt++;
		}
		if (c == 'h' && qt != 0 && str[idx + 1] == '\0')
			cnt++;
		idx++;
	}
	return (cnt);
}

int	substitute_dollar_sign(t_data *meta, t_cmd_list *cmd, char *s, char c)
{
	t_tmp	*node;
	char	**tmp;
	int		*keep;
	int		var;

	if (search_chr_in_str(s, '$') == 0)
		return (1);
	var = measure_length_quote_set(s, var = 0, c);
	tmp = dividing_sub_token(s, var);
	if (tmp == NULL)
		return (0);
	node = do_substitute_dollar_sign(meta, tmp, c);
	free_sndry_arr((void **)tmp);
	if (node == NULL)
		return (0);
	var = join_sub_tokens(cmd, node, c, -1);
	if (var == 0)
		return (0);
	free_t_tmp(node);
	return (1);
}

int	substitute_tokens(t_data *meta, t_list *tokens, char c)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (c == 'c')
		{
			if (check_quote_valid(tmp->token) == 0)
				return (0);
		}
		/*
		if (subtitute_dollar_sign(meta, tmp, c) == 0)
			return (0);
		if (c == 'c')
		{
			if (substitute_wildcard(tmp) == -1)
				return (0);
			if (remove_quote_tokens(tmp) == 0)
				return (0);
		}
		*/
		tmp = tmp->next;
	}
	return (1);
}
