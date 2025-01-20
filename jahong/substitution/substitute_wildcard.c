/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 14:40:42 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_wild_card(void)
{
	char	*tmp;
	char	*wild_card;
	int		len;
	int		idx;

	idx = 0;
	wild_card = "file file 42 test path";
	len = ft_strlen(wild_card);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (memory_alloc_error());
	while (wild_card[idx] != '\0')
	{
		tmp[idx] = wild_card[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}
int	change_rest_whildcard(char **str)
{
	char	*tmp;
	int		row;

	row = 0;
	while (str[row] != NULL)
	{
		if (str[row][0] == '*')
		{
			tmp = change_null_string();
			if (tmp == NULL)
				return (-1);
			free(str[row]);
			str[row] = tmp;
			tmp = NULL;
		}
		row++;
	}
	return (1);
}
int	check_path_or_var(char *str)
{
	int idx;
	int	bp;
	int	slash;

	idx = 0;
	bp = 1;
	slash = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == ' ')
		{
			bp = 0;
			return (bp);
		}
		if (str[idx] == '/')
			slash = 2;
		idx++;
	}
	if (slash == 0 && str[0] != 0 && str[0] != '*')
		bp = 0;
	if (bp == 0)
		return (bp);
	if (slash == 2)
		return (slash);
	return (bp);
}
int	rest_wildcard(char **str, int quote, int len)
{
	int	row;
	int	path;
	int	keep;
	int flag;

	row = 0;
	keep = 0;
	path = 0;
	flag = 0;
	if (quote != 0)
		return (0);
	while (str[row] != NULL)
	{
		keep = check_path_or_var(str[row]);
		if (keep == 2)
			flag = 1;
		path += keep;
		if (str[row][0] == '*' && flag == 0)
		 	path += search_character_into_str(str[row], '*');
		row++;
	}
	if (path - len == 1)
		return (change_rest_whildcard(str));
	return (0);
}
int	exchange_str_wildcard(char **str, int len)
{
	char	*tmp;
	int		row;
	int		flag;

	row == 0;
	flag = 0;
	while (str[row] != NULL)
	{
		if (str[row][0] == '*' && flag == 0)
		{
			tmp = change_wild_card();
			if (tmp == NULL)
				return (-1);
			free(str[row]);
			str[row] = tmp;
			tmp = NULL;
			flag = 1;
		}
		else if (str[row][0] != '\0')
		{
			tmp = change_null_string();
			if (tmp == NULL)
				return (-1);
			free(str[row]);
			str[row] = tmp;
			tmp = NULL;
		}
		row++;
	}
	return (flag);
}
int	count_ck_wc(char *ck_wc, int len)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 1;
	while (idx < len)
	{
		if (ck_wc[idx] != 1)
			flag = 0;
		idx++;
	}
	return (flag);
}
void	memo_wildcard_true_false(char **str, char *ck_wc)
{
	char	*tmp;
	int		row;
	int		col;
	int		ck;

	row = 0;
	while (str[row] != NULL)
	{
		col = 0;
		ck_wc[row] = 1;
		ck_wc[row] = are_all_characters_same(str[row], '*');
		row++;
	}
	return ;
}
int	substitute_wildcard(t_data *meta, char **str, int quote, int flag)
{
	char	*ck_wc;
	int		len;
	int		result;
	int		temp;

	result = 0;
	len = sndry_arr_len((void **)str);
	ck_wc = (char *)malloc(sizeof(int) * (len));
	if (ck_wc == NULL)
		return ((memory_alloc_error(), -1));
	memo_wildcard_true_false(str, ck_wc);
	temp = count_ck_wc(ck_wc, len);
	// if ((len == 1 && ck_wc[0] == 1) || temp == 1)
	// 	return ((free(ck_wc), exchange_str_wildcard(str, len))); // quote 기준으로 나눴을 때 '$HOME'$**** 처리가 안됨
	while (result < len)
	{
		printf("ck_wc[%d] = %d\n", result, ck_wc[result]);
		result++; 
	}
	
	if (temp != 1)
	{
		if (flag != 1)
			return ((free(ck_wc), 0));
		else
			return ((free(ck_wc), rest_wildcard(str, quote, len)));
	}
	return (1);
}
