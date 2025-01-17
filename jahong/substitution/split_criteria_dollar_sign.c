/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_criteria_dollar_sign.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:50:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/17 16:52:06 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_null_string(void)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	tmp[0] = '\0';
	return (tmp);
}

char	*searching_from_envval(t_data *meta, t_list *tokens, char *str)
{
	t_path	*tmp;
	int		len;

	tmp = meta->env;
	len = ft_strlen(str);
	if (str[len - 1] == '$')
		return (copy_current_process_pid());
	while (tmp != NULL)
	{
		if (ft_strncmp(&str[1], tmp->key, ft_strlen(&str[1])) == 0)
			return (copy_env_value(tmp->value));
		tmp = tmp->next;
	}
	return (change_null_string());
}

int	matching_env_val_n_change(t_data *meta, t_list *tokens, char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		if (count_dollar_sign(str[row]) == 1 && ft_strlen(str[row]) > 1)
		{
			tmp = searching_from_envval(meta, tokens, str[row]);
			if (tmp == NULL)
				return (0);
			if (tmp != str[row])
			{
				free(str[row]);
				str[row] = tmp;
				tmp = NULL;
			}
		}
		row++;
	}
	return (1);
}

char	*change_dollar_sign(t_data *meta, t_list *tokens, char *str, int len)
{
	char	**tmp;
	int		result;
	int cnt = 0;

	tmp = div_copy_token(str, len);
	if (tmp == NULL)
		return (NULL);
	while (tmp[cnt] != NULL)
	{
		printf("before div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	result = matching_env_val_n_change(meta, tokens, tmp);
	if (result == 0)
		return (free_sndry_arr((void **)tmp));
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		printf("after div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	return (NULL);
}
int	dollar_sign_into_str(char *str, int idx, int flag, int quote)
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
		else if (flag == 2)
		{
			if (check_quote_pair(str[idx], 0) != 0)
				cnt++;
			else if (str[idx] == ' ')
			{
				cnt++;
				flag = 1;
			}
		}
		idx++;
	}
	return (cnt);
}

int	check_split_point_str(char *str, int idx, int flag, int quote) // 줄 수 조정
{
	int	cnt;

	cnt = 0;
	// if (quote == 2)
	// 	cnt = dollar_sign_into_string(str, idx, flag, quote);
	// else
	// {
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
				if (str[idx + 1] == '$' || check_valid_back(str, idx + 1) != 0)
				{
					idx++;	
					flag = 0;
				}
			}
			else if (flag == 2)
			{
				if (check_quote_pair(str[idx], 0) != 0)
					cnt++;
				else if (str[idx] == ' ' || ft_isspecial_chr(str[idx]) != 0)
				{
					cnt++;
					flag = 1;
				}
			}
			idx++;
		}
	// }
	return (cnt);
}
char	*search_n_change_dollar_sign(t_data *meta, t_list *tokens, char *str)
{
	char	*tmp;
	int		idx;
	int		flag;
	int		cnt;
	int		quote;

	idx = 0;
	flag = 0;
	quote = check_quote_pair(str[0], 0);
	if (quote == 1)
		return (str);
	cnt = check_split_point_str(str, idx, flag, quote);
	if (cnt == 0)
		return (str);
	tmp = change_dollar_sign(meta, tokens, str, cnt);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}