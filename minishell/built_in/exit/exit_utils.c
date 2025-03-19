/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:39:26 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/19 17:45:15 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	check_not_digit(char *str)
{
	int	index;
	int	check_operator;
	int	output;

	index = 0;
	check_operator = 0;
	output = 0;
	while (str[index] == '-' || str[index] == '+')
	{
		index++;
		check_operator++;
	}
	while (str[index] != '\0')
	{
		if (('0' <= str[index] && str[index] <= '9'))
			output = 1;
		else
			return (0);
		index++;
	}
	if (check_operator > 1)
		return (0);
	return (output);
}

int	ft_strlen_zero_pass(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i + j] != '\0')
		j++;
	return (j);
}

long long	ft_atoi_long_long(const char *string)
{
	long long	i;
	long long	nb;
	long long	count;
	long long	j;

	i = 0;
	j = 0;
	count = 1;
	nb = 0;
	while (string[i] == 32 || (9 <= string[i] && string[i] <= 13))
		i++;
	while (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			count *= -1;
		i++;
		j++;
	}
	if (j > 1)
		return (0);
	while ('0' <= string[i] && string[i] <= '9')
		nb = (nb * 10) + (string[i++] - 48);
	return (nb * count);
}

int	parsing_digit_longlong_max(char *str)
{
	if (check_not_digit(str) == 0)
		return (0);
	if (ft_strlen_zero_pass(str) > 19)
		return (0);
	if (check_overflow(str) != 0)
		return (0);
	g_ws = (int)ft_atoi_long_long(str);
	return (1);
}
