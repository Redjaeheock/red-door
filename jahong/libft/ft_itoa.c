/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:59:43 by jahong            #+#    #+#             */
/*   Updated: 2025/02/18 20:07:38 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define INT_MIN -2147483648

static char	*change_int_to_ascii(int n, int len, int negative)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[len] = '0';
	while (n > 0)
	{
		str[len--] = n % 10 + 48;
		n /= 10;
	}
	if (negative == 1)
		str[0] = '-';
	return (str);
}

static int	length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	if (len == 0)
		len = 1;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		negative;
	int		orgn;

	orgn = n;
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		if (n == INT_MIN)
			n++;
		n *= -1;
	}
	len = length(n);
	str = change_int_to_ascii(n, len + negative, negative);
	if (str == NULL)
		return (NULL);
	if (orgn == INT_MIN)
		str[len] += 1;
	return (str);
}
/*
#include <stdio.h>
int main()
{
	int n = 5;
	printf("%s", ft_itoa(n));
	return (0);
}*/
