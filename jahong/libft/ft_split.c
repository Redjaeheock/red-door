/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:50:35 by jahong            #+#    #+#             */
/*   Updated: 2025/01/10 12:07:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void *free_arr(char **arr)
{
	int	idx;

	idx = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[idx] != NULL)
	{
		free(arr[idx]);
		arr[idx] = NULL;
		idx++;
	}
	free(arr);
	return (NULL);
}
static char	**allocate_secondary_array(int len)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	return (arr);
}
static char	*copy_str(char *str, char c, int *idx)
{
	char	*cp_str;
	int		cnt;

	cnt = 0;
	while (str[*idx] == c)
		*idx += 1;
	while (str[*idx + cnt] != c && str[*idx + cnt] != '\0')
		cnt++;
	cp_str = (char *)malloc(sizeof(char) * (cnt + 1));
	if (cp_str == NULL)
		return (NULL);
	cnt = 0;
	while (str[*idx] != c && str[*idx] != '\0')
	{
		cp_str[cnt] = str[*idx];
		cnt++;
		*idx += 1;
	}
	cp_str[cnt] = '\0';
	return (cp_str);
}
static char	**div_word(char *s, char c, int cnt)
{
	char	**array;
	int		row;
	int		idx;

	idx = 0;
	row = 0;
	array = allocate_secondary_array(cnt);
	if (array == NULL)
		return (NULL);
	while (row < cnt)
	{
		array[row] = copy_str(s, c, &idx);
		if (array[row] == NULL)
			return (free_arr(array));
		row++;
	}
	array[row] = NULL;
	return (array);
}
char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		idx;
	int		cnt;

	idx = 0;
	cnt = 0;
	if (s == NULL)
		return (NULL);
	while (((char *)s)[idx] == c)
		idx++;
	while (((char *)s)[idx] != '\0')
	{
		if ((((char *)s)[idx] == c) && ((char *)s)[idx - 1] != c)
			cnt++;
		else if (((char *)s)[idx] != c && ((char *)s)[idx + 1] == '\0')
			cnt++;
		idx++;
	}
	if (cnt == 0)
		cnt = 1;
	arr = div_word((char *)s, c, cnt);
	return (arr);
}