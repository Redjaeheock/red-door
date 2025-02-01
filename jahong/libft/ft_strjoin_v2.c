/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:36:25 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 16:56:58 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_v2(const char *s1, const char *s2)
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
		return (memory_alloc_error());
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