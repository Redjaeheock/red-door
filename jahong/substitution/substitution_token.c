/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/17 16:01:57 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	substitution_dollar_sign_to_envval(t_data *meta, t_list *tokens, char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		tmp = search_n_change_dollar_sign(meta, tokens, str[row]);
		if (tmp == NULL)
		{
			free_sndry_arr((void **)str);
			return (0);
		}
		if (tmp != str[row])
		{
			free(str[row]);
			str[row] = tmp;
			tmp = NULL;
		}
		row++;
	}
	//join 코드
	return (1);
}

int	count_dollar_sign(char *str)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '$')
		{
			flag = 1;
			return (flag);
		}
		idx++;
	}
	return (flag);
}
int	mapping_dollar_sign(t_data *meta, t_list *tokens)
{
	char	**tmp;
	int		row;
	int		result;
	int cnt = 0;

	if (count_dollar_sign(tokens->token) == 0)
		return (1);
	row = measure_length_quote_set(tokens->token, row = 0);
	tmp = temporary_copy_token(tokens->token, row);
	if (tmp == NULL)
		return (0);
	while (tmp[cnt] != NULL)
	{
		printf("split quote %s\n", tmp[cnt]);
		cnt++;
	}
	result = substitution_dollar_sign_to_envval(meta, tokens, tmp);
//	free_sndry_arr((void **)tmp);
	if (result == 0)
		return (0);

	return (0); // 1 로 전환
}
int	check_quote_valid(char *token)
{
	int	idx;
	int quote;
	int	cnt;

	idx = 0;
	quote = 0;
	cnt = 0;
	while (token[idx] != '\0')
	{
		quote = check_quote_pair(token[idx], quote);
		idx++;
	}
	if (quote != 0)
	{
		error_qoute(quote);
		return (0);
	}
	return (1);
}
int	substitution_env_var(t_data *meta, t_list *tokens)
{
	while (tokens != NULL)
	{
		if (check_quote_valid(tokens->token) == 0)
			return (0);
		if (mapping_dollar_sign(meta, tokens) == 0);
			return (0);
		tokens = tokens->next;
	}
	return (1);
}