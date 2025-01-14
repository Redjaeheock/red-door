/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitusion_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:34:43 by jahong            #+#    #+#             */
/*   Updated: 2025/01/14 14:55:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_partial_token(char *str, int idx, int end)
{
	printf("start func3\n");
	char	*tmp;
	int		len;
	int		i;

	len = end - idx;
	i = 0;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		tmp[i] = str[idx];
		i++;
		idx++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*temporary_div_token(char *str, int *idx, int quote)
{
	printf("start func2\n");
	char	*tmp;
	int		len;
	int		start;

	start = *idx;
	while (str[*idx] != '\0')
	{
		printf("curren str[%d] = %c\n", *idx, str[*idx]);
		if (quote == 0 && check_quote_pair(str[*idx + 1], quote) != 0)		
			break;
		else if (quote == 1 && check_quote_pair(str[*idx], quote) == 0)
			break ;
		else if (quote == 2 && check_quote_pair(str[*idx], quote) == 0)
			break ;
		*idx++;
	}
	tmp = extract_partial_token(str, start, *idx);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	**temporary_copy_token(char *str, int len)
{
	printf("start func1\n");
	char	**tmp;
	int		row;
	int		idx;
	int		quote;
	int cnt = 0;

	row = 0;
	idx = 0;
	quote = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	while (row < len)
	{
		quote = check_quote_pair(str[idx], quote);
		tmp[row] = temporary_div_token(str, &idx, quote);
		if (tmp[row] == NULL)
			return (free_sndry_arr((void **)tmp));
		row++;
	}
	while (tmp[cnt] != NULL)
	{
		printf("%s\n", tmp[cnt]);
		cnt++;
	}
	return (tmp);
}

int	count_dollar_sign(char *str)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '$')
		{
			cnt++;
			if (str[idx + 1] == '$')
				idx++;
		}
		idx++;
	}
	return (cnt);
}

int	measure_length_quote_set(char *s, int cnt)
{
	int	idx;
	int qote;

	idx = 0;
	qote = 0;
	while (s[idx] != '\0')
	{
		if (qote == 0) 
		{
			if (s[idx] == '\'')
				qote = 1;
			else if (s[idx] == '"')
				qote = 2;
			else if (idx == 0 || s[idx - 1] == '\'' || s[idx - 1] == '"')
				cnt++;
		}
		else if ((qote == 1 && s[idx] == '\'') || (qote == 2 && s[idx] == '"'))
		{
			qote = 0;
			cnt++;
		}
		idx++;
	}
	return (cnt);
}

int	mapping_dollor_sign(t_list *tokens)
{
	int	row;
	char	**tmp;

	row = measure_length_quote_set(tokens->token, row = 0);
	printf("row = %d\n", row);
	tmp = temporary_copy_token(tokens->token, row);

	//len = count_dollar_sign(tokens->token);
	//dollars = malloc(sizeof(int) * len);
	//if (dollars == NULL)
	//	return (0);
	///check_dollar_sign_invalid(tokens->token, dollars, len);
	// if (dollar_flag == 1 && quote != 1)
	// 	str = ch_dollar_to_envval(tokens->token, dollar_idx, quote);
	// else
	// 	str = cp_dollar_to_toekn(tokens->token);
	return (0);
	
}
int	check_quote_invalid(char *token)
{
	int	idx;
	int quote;

	idx = 0;
	quote = 0;
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