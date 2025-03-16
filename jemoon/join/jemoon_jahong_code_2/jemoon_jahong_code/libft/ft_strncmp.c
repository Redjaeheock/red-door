/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:29:02 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 19:32:34 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, const char *s2, unsigned int n)
{
	unsigned int	len;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	len = 0;
	while (len < n && (str1[len] != '\0') || (str2[len] != '\0'))
	{
		if (str1[len] - str2[len] != 0)
			return (str1[len] - str2[len]);
		len++;
	}
	return (0);
}
