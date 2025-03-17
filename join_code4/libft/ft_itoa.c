/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:59:43 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 19:29:18 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change(char *str, int n, int len, int flag)
{
	str[len--] = '\0';
	if (n == 0)
		str[len] = '0';
	while (n > 0)
	{
		str[len--] = n % 10 + 48;
		n /= 10;
	}
	if (flag)
		str[0] = '-';
}

static int	length(int n)
{
	int	len;

	len = 0;
	if (!(n))
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		flag;
	int		orgn;

	orgn = n;
	flag = 0;
	if (n < 0)
	{
		flag = 1;
		if (n == -2147483648)
			n++;
		n *= -1;
	}
	len = length(n);
	if (!(len))
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + 1 + flag));
	if (str == NULL)
		return (NULL);
	change(str, n, len + flag, flag);
	if (orgn == -2147483648)
		str[len] += 1;
	return (str);
}
