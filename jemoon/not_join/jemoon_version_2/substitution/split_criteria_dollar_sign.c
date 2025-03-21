/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_criteria_dollar_sign.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:50:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/21 22:27:11 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*searching_from_envval(t_data *meta, char *str)
{
	t_path	*tmp;
//	int		len;

	tmp = meta->env;
//	len = ft_strlen(str);
	/*
	if (str[len - 1] == '$')
		return (copy_current_process_pid());
	if (str[0] == '$' && str[1] == '?')
		return (get_exit_no());
	*/
	while (tmp != NULL)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(str)) == 0)
			return (copy_env_value(tmp->value));
		tmp = tmp->next;
	}
	return (change_null_string());
}

int	matching_env_val_n_change(t_data *meta, char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		if (count_dollar_sign(str[row]) == 1 && ft_strlen(str[row]) > 1)
		{
			tmp = searching_from_envval(meta, str[row]);
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

char	*change_dollar_sign(t_data *meta, char *str, int len)
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
	result = matching_env_val_n_change(meta, tmp);
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
int	check_split_point_str(char *str, int idx, int flag)
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
	return (cnt);
	// 줄 수 조정
}
char	*search_n_change_dollar_sign(t_data *meta, char *str)
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
	cnt = check_split_point_str(str, idx, flag);
	if (cnt == 0)
		return (str);
	tmp = change_dollar_sign(meta, str, cnt);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
