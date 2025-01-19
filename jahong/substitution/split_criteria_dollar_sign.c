/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_criteria_dollar_sign.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:50:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 22:13:21 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_from_envval(t_data *meta, t_list *tokens, char *str, int *flag)
{
	t_path	*tmp;
	int		len;

	tmp = meta->env;
	len = ft_strlen(str);
	if (str[len - 1] == '$')
		return (copy_current_process_pid());
	if (str[0] == '$' && str[1] == '?')
		return (get_exit_no());
	while (tmp != NULL)
	{
		if (ft_strcmp(&str[1], tmp->key) == 0)
		{
			*flag = 1;
			return (copy_env_value(tmp->value));
		}
		else if (str[0])
		tmp = tmp->next;
	}
	return (change_null_string());
}
int	matching_env_val_n_change(t_data *meta, t_list *tokens, char **str)
{
	char	*tmp;
	int		row;
	int		flag;

	row = 0;
	flag = 0;
	while (str[row] != NULL)
	{
		if (search_dollar_sign_into_token(str[row]) == 1 && ft_strlen(str[row]) > 1)
		{
			tmp = search_from_envval(meta, tokens, str[row], &flag);
			if (tmp == NULL)
				return (-1);
			if (tmp != str[row])
			{
				free(str[row]);
				str[row] = tmp;
				tmp = NULL;
			}
		}
		row++;
	}
	return (flag);
}
char	*change_dollar_sign(t_data *meta, t_list *tokens, char *str, int len)
{
	char	**tmp;
	char	*join;
	int		result;
	int		quote;
	int cnt = 0;

	quote = check_quote_pair(str[0], 0);
	tmp = div_copy_token(str, len, quote);
	if (tmp == NULL)
		return (NULL);
	while (tmp[cnt] != NULL)
	{
		printf("before div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	result = matching_env_val_n_change(meta, tokens, tmp);
	if (result == -1)
		return (free_sndry_arr((void **)tmp));
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		printf("after div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	result = substitution_wildcard(meta, tmp, quote, result);
	if (result == -1)
		return (free_sndry_arr((void **)tmp));
	printf("\n");
	join = join_div_tokens(tmp, result);
	if (join == NULL)
		(free_sndry_arr((void **)tmp));
	return (join);
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
			else if (str[idx] == ' ' || ft_isspecial_chr(str[idx]) != 0)
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
char	*search_n_change_dollar_sign(t_data *meta, t_list *tokens, char *str)
{
	char	*tmp;
	int		cnt;
	int		quote;

	quote = check_quote_pair(str[0], 0);
	if (quote == 1)
		return (str);
	cnt = check_split_point_str(str);
	if (cnt == 0)
		return (str);
	printf("cnt =========================== %d\n", cnt);
	tmp = change_dollar_sign(meta, tokens, str, cnt);
	if (tmp == NULL)
		return (NULL);
	printf(">>>>>> after change str = %s\n", tmp);
	return (tmp);
}
