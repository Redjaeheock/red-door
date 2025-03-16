/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:04:45 by jahong            #+#    #+#             */
/*   Updated: 2025/01/26 14:40:00 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*incycle(char *base, char *str, size_t str_len, size_t lmt)
{
	size_t	b_idx;
	size_t	s_idx;

	b_idx = 0;
	s_idx = 0;
	while ((b_idx < lmt) && (base[b_idx] != '\0' && str[s_idx] != '\0'))
	{
		if (base[b_idx] == str[s_idx])
		{
			s_idx++;
			if (s_idx == str_len)
				return (&base[b_idx + 1 - s_idx]);
			b_idx++;
		}
		else
		{
			b_idx += 1 - s_idx;
			s_idx = 0;
		}
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	ltl_idx;

	if (little == NULL)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	ltl_idx = ft_strlen(little);
	return (incycle((char *)big, (char *)little, ltl_idx, len));
}

/*
#include <stdio.h>
int main (){

	char *a = "";
	char *b = "";
	printf("%s, %s\n-> %s", a, b, ft_strnstr(a,b,3));
	return 0;
}*/
