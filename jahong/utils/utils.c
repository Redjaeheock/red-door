/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:50 by jahong            #+#    #+#             */
/*   Updated: 2025/01/18 22:55:19 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*wild_card_substitution(void)
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
		return (NULL);
	while (wild_card[idx] != '\0')
	{
		tmp[idx] = wild_card[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}

char	*str_join(char const *s1, char const *s2)
{
	int		len;
	char	*cat_arr;
	int		idx;
	int		cnt;

	idx = 0;
	cnt = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	cat_arr = (char *)malloc(sizeof(char) * (len + 1));
	if (cat_arr == NULL)
		return (NULL);
	while (s1 != NULL && (s1[idx] != '\0'))
	{
		cat_arr[idx] = s1[idx];
		idx++;
	}
	while (s2 != NULL && (s2[cnt] != '\0'))
	{
		(cat_arr)[idx + cnt] = s2[cnt];
		cnt++;
	}
	cat_arr[idx + cnt] = '\0';
	return (cat_arr);
}
char	*join_div_tokens(char **tmp, int quote, int flag)
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