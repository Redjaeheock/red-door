/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:00:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/15 21:50:47 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *copy_split_token()

char	*split_token(char *str, int *idx)
{
	char	*tmp;
	int		start;

	start = *idx;
	if (str[*idx] != '$')
	{
		while (str[*idx] != '$')
			*idx += 1;
	}
	else
	{
		*idx += 1;
		while (str[*idx] != '\0')
		{
			if (str[*idx] == '$' || str[*idx] != ' ')
				break ;
			else if (check_quote_pair(str[*idx], 0) != 0)
				break ;
			*idx += 1;
		}
	}
	tmp = copy_split_token(str, start, *idx);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	**div_copy_token(char *str, int len)
{
	char	**tmp;
	int		row;
	int		idx;

	row = 0;
	idx = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (row <= len)
	{
		tmp[row] = split_token(str, &idx);
		if (tmp[row] == NULL)
			return (sndry_alloc_err(tmp));
		row++;
	}

}

char	*change_dollar_sign(t_list *tokens, char *str, int idx, int len)
{
	char	**tmp;

	tmp = div_copy_token(str, len);
	if (tmp == NULL)
		return (NULL);
	return (NULL);
}

int	count_dollar_sign(char *str, int idx, int flag)
{
	int	cnt;

	cnt = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] != '$' && flag == 0)
		{
			cnt++;
			flag = 1;
		}
		else if (str[idx] == '$')
		{
			cnt++;
			flag = 2;
			if (str[idx + 1] == '$')
			{
				idx++;
				flag = 0;
			}
		}
		else if (check_quote_pair(str[idx], 0) != 0 && flag == 2)
			cnt++;
		idx++;
	}
	return (cnt);
}
char	*search_n_change_dollar_sign(t_list *tokens, char *str)
{
	char	*tmp;
	int		idx;
	int		flag;
	int		cnt;

	idx = 0;
	flag = 0;
	cnt = count_dollar_sign(str, idx, flag);
	if (cnt == 0)
		return (str);
	printf("cnt = %d\n", cnt);
	tmp = change_dollar_sign(tokens, str, idx, cnt);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*substitution_dollar_sign_to_envval(t_list *tokens, char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		if (check_quote_pair(str[row][0], 0) == 1)
			continue ;
		tmp = search_n_change_dollar_sign(tokens, str[row]);
		if (tmp == NULL)
		{
			free_sndry_arr((void **)str);
			return (NULL);
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
	return (str);
}

int	mapping_dollor_sign(t_list *tokens)
{
	int		row;
	char	**tmp;
	char	*result;
	int cnt = 0;

	row = measure_length_quote_set(tokens->token, row = 0);
	tmp = temporary_copy_token(tokens->token, row);
	if (tmp == NULL)
		return (0);
	while (tmp[cnt] != NULL)
	{
		printf("%s\n", tmp[cnt]);
		cnt++;
	}
	result = substitution_dollar_sign_to_envval(tokens, tmp);
	free_sndry_arr((void **)tmp);
	if (result == NULL)
		return (0);

	return (0);
}
int	check_quote_invalid(char *token)
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
int	substitution_env_var(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (check_quote_invalid(tokens->token) == 0)
			return (0);
		if (mapping_dollor_sign(tokens) == 0);
			return (0);
		tokens = tokens->next;
	}
	return (1);
}