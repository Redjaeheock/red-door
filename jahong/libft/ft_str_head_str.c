/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_head_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:38:03 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 12:09:02 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *check_big_head(char *base, char *str, int big_len, int str_len)
{
	int	b_idx;
	int	s_idx;
	int	cnt;

	b_idx = 0;
	s_idx = 0;
	cnt = 0;
	while ((base[b_idx] != '\0' && str[s_idx] != '\0') && (b_idx < big_len))
	{
		if (base[b_idx] == str[s_idx])
		{
			cnt++;
			if (cnt == str_len)
				return (base);
			b_idx++;
			s_idx++;
		}
		else
			break ;
	}
	return (NULL);
}

char	*ft_str_head_str(const char *big, const char *little)
{
	int	big_len;
	int	little_len;

	if (little == NULL || little[0] == '\0')
		return (NULL);
	if (big == NULL || big[0] == '\0')
		return (NULL);
	big_len = ft_strlen(big);
	little_len = ft_strlen(little);
	if (big[0] != little[0])
		return (NULL);
	return (check_big_head((char *)big, (char *)little, big_len, little_len));
	
}