/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_dollar_sign.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:50:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 20:19:03 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	conditinal_change_address(char **str1, char **str2)
{
	if (are_all_characters_same(*str1, '*') == 1)
		*str1 = NULL;
	else if (are_all_characters_same(*str2, '*') == 1)
		*str2 = NULL;
	return ;
}

char	*join_wildcard_exception(char *str1, char *str2)
{
	char	*tmp;
	int		len;
	int		idx;
	int		n;

	idx = 0;
	n = 0;
	conditinal_change_address(&str1, &str2);
	len = ft_strlen(str1) + ft_strlen(str2);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (memory_alloc_error());
	while (str1 != NULL && str1[idx] != '\0')
	{
		tmp[idx] = str1[idx];
		idx++;
	}
	while (str2 != NULL && str2[n] != '\0')
	{
		tmp[idx + n] = str2[n];
		n++;
	}
	tmp[idx + n] = '\0';
	return (tmp);
}

int	measure_length_copied_sub_token(char **str)
{
	int	row;
	int	cnt;

	row = 0;
	cnt = 0;
	while (str[row] != NULL)
	{
		if (are_all_characters_same(str[row], '*') == 1)
		{
			row++;
			continue ;
		}
		row++;
	}
	return (row);
}

char	**join_diveded_copied_token(char **str)
{
	printf("\nstart jing tmp\n");
	char	**ttmp;
	char	*tmp;
	int		row;
	int		len;

	row = 0;
	len =  measure_length_copied_sub_token(str);
	tmp = str[row++];
	ttmp = (char **)malloc(sizeof(char *) * (len + 1));
	if (ttmp == NULL)
		return (sndry_alloc_err(NULL));
	while (row < len)
	{
		ttmp[row] = join_wildcard_exception(tmp, str[row + 1]);
		if (tmp == NULL)
			return (free_sndry_arr((void **)ttmp));
		
		
		row++;
	}
	ttmp[row] = NULL;
	return (ttmp);
}

char	*search_in_envpath(t_data *meta, char *str, int *flag)
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
			return (ft_strdup(tmp->value));
		}
		else if (str[0])
		tmp = tmp->next;
	}
	return (change_null_string());
}
int	mapping_dollar_sign_to_env(t_data *meta, char **str)
{
	char	*tmp;
	int		row;
	int		flag;

	row = 0;
	flag = 0;
	while (str[row] != NULL)
	{
		if (search_chr_in_str(str[row], '$') == 1 && ft_strlen(str[row]) > 1)
		{
			tmp = search_in_envpath(meta, str[row], &flag);
			if (tmp == NULL)
				return ((sndry_alloc_err(NULL), -1));
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
char	**change_dollar_sign(t_data *meta, char *str, int len)
{
	char	**tmp;
	char	**join;
	int		result;
	int		quote;
	int cnt = 0;

	quote = check_quote_pair(str[0], 0);
	tmp = dividing_copied_token(str, len, quote);
	if (tmp == NULL)
		return (NULL);
	while (tmp[cnt] != NULL)
	{
		printf("before div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	result = mapping_dollar_sign_to_env(meta, tmp);
	if (result == -1)
		return (free_sndry_arr((void **)tmp));
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		printf("after div tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	result = substitute_wildcard(meta, tmp, quote, result);
	if (result == -1)
		return (free_sndry_arr((void **)tmp));
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		printf("substituted v1 tmp = %s\n", tmp[cnt]);
		cnt++;
	}
	printf("\n");
	// join = join_diveded_copied_token(tmp);
	// if (join == NULL)
	// 	(free_sndry_arr((void **)tmp));
	// return (join);
	return (NULL);
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
char	*search_n_change_dollar_sign(t_data *meta, char *str)
{
	char	**tmp;
	int		cnt;
	int		quote;

	quote = check_quote_pair(str[0], 0);
	if (quote == 1)
		return (str);
	cnt = check_split_point_str(str);
	if (cnt == 0)
		return (str);
	printf("cnt =========================== %d\n", cnt);
	tmp = change_dollar_sign(meta, str, cnt);
	if (tmp == NULL)
		return (NULL);
	cnt = 0;
	while (tmp[cnt] != NULL)
	{
		printf(">>>>>> join the tmp string = %s\n", tmp[cnt]);
		cnt++;
	}
	return (NULL);
}
int	substitute_dollar_sign(t_data *meta, char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		tmp =  search_n_change_dollar_sign(meta, str[row]);
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
