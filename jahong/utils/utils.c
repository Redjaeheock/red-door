/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:50 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 15:57:26 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	search_chr_in_str(char *str, char c)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == c)
		{
			flag = 1;
			break ;
		}
		idx++;
	}
	return (flag);
}
char	are_all_characters_same(char *str, char c)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 1;
	while (str[idx] != '\0')
	{
		if (str[idx] != c)
		{
			flag = 0;
			break ;
		}
		idx++;
	}
	return (flag);
}
char	*str_join(char const *s1, char const *s2)
{
	char	*cat_arr;
	int		len;
	int		idx;
	int		n;

	idx = 0;
	n = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	cat_arr = (char *)malloc(sizeof(char) * (len + 1));
	if (cat_arr == NULL)
		return (NULL);
	while (s1 != NULL && (s1[idx] != '\0'))
	{
		cat_arr[idx] = s1[idx];
		idx++;
	}
	while (s2 != NULL && (s2[n] != '\0'))
	{
		(cat_arr)[idx + n] = s2[n];
		n++;
	}
	cat_arr[idx + n] = '\0';
	return (cat_arr);
}
char	*join_div_tokens(char **tmp, int flag)
{
	char	*str1;
	char	*str2;
	int		row;

	str1 = NULL;
	str2 = NULL;
	row = 0;
	while (tmp[row] != NULL)
	{
		str2 = str_join(str1, tmp[row]);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		row++;
	}
	return (str1);
}
char	*get_exit_no(void)
{
	char *tmp;
	char *exit_no;
	int	idx;
	int	len;

	idx = 0;
	// exit no itoa 처리
	exit_no = "99999";
	len = ft_strlen(exit_no);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (exit_no[idx] != '\0')
	{
		tmp[idx] = exit_no[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}