/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:47:14 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 19:19:17 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// long	ft_strtol(const char *nptr, char **endptr, int base)
// {
// 	int	idx;
// 	int	sign;

// 	idx = 0;
// 	sign = 1;
// 	while (('\t' <= ((char *)nptr)[idx] && ((char *)nptr)[idx] <= '\r')
// 		|| ((char *)nptr)[idx] == ' ')
// 		idx++;
// 	if (((char *)nptr)[idx] == '-' || ((char *)nptr)[idx] == '+')
// 	{
// 		if (((char *)nptr)[idx] == '-')
// 			sign *= -1;
// 		idx++;
// 	}
// 	if (ft_isdigit(((char *)nptr)[idx]))
// 		return (count_digit((char *)nptr, idx) * (sign));
// 	return (0);
// }