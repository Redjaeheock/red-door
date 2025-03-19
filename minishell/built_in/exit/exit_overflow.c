/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_overflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:44:33 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/19 17:44:53 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	check_positive_overflow(char *num_str)
{
	char	*max_str;
	int		len;
	int		i;

	max_str = "9223372036854775807";
	len = ft_strlen(num_str);
	i = 0;
	if (num_str[i] == '+')
		i++;
	if (len - i > 19)
		return (-1);
	if (len - i == 19)
	{
		while (i < 19)
		{
			if (num_str[i] > max_str[i])
				return (-1);
			if (num_str[i] < max_str[i])
				return (0);
			i++;
		}
	}
	return (0);
}

int	check_negative_overflow(char *num_str)
{
	char	*min_str;
	int		len;
	int		i;

	min_str = "-9223372036854775808";
	len = ft_strlen(num_str);
	i = 0;
	if (num_str[i] == '-')
		i++;
	if (len - i > 19)
		return (-1);
	if (len - i == 19)
	{
		while (i < 20)
		{
			if (num_str[i] < min_str[i])
				return (0);
			if (num_str[i] > min_str[i])
				return (-1);
			i++;
		}
	}
	return (0);
}

int	check_overflow(char *num_str)
{
	int	i;

	i = 0;
	if (ft_strlen(num_str) == 0)
		return (-1);
	if (num_str[0] == '-')
		return (check_negative_overflow(num_str));
	else
		return (check_positive_overflow(num_str));
}
