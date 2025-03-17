/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:43:48 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 17:15:58 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_digit(char *str, int idx)
{
	int	num;
	int	len;

	num = 0;
	len = ft_strlen(str);
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		num = (num * 10) + (str[idx] - 48);
		idx++;
	}
	if (idx < len)
		return (0);
	return (num);
}

int	ft_atoi(const char *nptr)
{
	int	idx;
	int	sign;

	idx = 0;
	sign = 1;
	while (('\t' <= ((char *)nptr)[idx] && ((char *)nptr)[idx] <= '\r')
		|| ((char *)nptr)[idx] == ' ')
		idx++;
	if (((char *)nptr)[idx] == '-' || ((char *)nptr)[idx] == '+')
	{
		if (((char *)nptr)[idx] == '-')
			sign *= -1;
		idx++;
	}
	if (ft_isdigit(((char *)nptr)[idx]))
		return (count_digit((char *)nptr, idx) * (sign));
	return (0);
}
