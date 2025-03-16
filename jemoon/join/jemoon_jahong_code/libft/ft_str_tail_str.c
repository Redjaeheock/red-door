/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tail_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:18:07 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 18:45:38 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_big_tail(char *base, char *str, int base_len, int str_len)
{
	int	b_idx;
	int	s_idx;
	int	cnt;

	b_idx = base_len - 1;
	s_idx = str_len - 1;
	cnt = 0;
	while (0 <= b_idx && 0 <= s_idx)
	{
		if (base[b_idx] == str[s_idx])
		{
			cnt++;
			if (cnt == str_len)
				return (base);
			b_idx--;
			s_idx--;
		}
		else
			break ;
	}
	return (NULL);
}

char	*ft_str_tail_str(const char *big, const char *little)
{

	int	big_len;
	int	little_len;

	if (little == NULL || little[0] == '\0')
		return (NULL);
	if (big == NULL || big[0] == '\0')
		return (NULL);
	big_len = ft_strlen(big);
	little_len = ft_strlen(little);
	if (big[big_len - 1] != little[little_len - 1])
		return (NULL);
	return (check_big_tail((char *)big, (char *)little, big_len, little_len));
}