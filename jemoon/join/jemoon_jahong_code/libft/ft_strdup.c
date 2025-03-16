/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:45:52 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 18:38:39 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*copy_str;
	int		len;
	int		idx;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	copy_str = (char *)malloc(sizeof(char) * (len + 1));
	if (copy_str == NULL)
		return (NULL);
	idx = 0;
	while (((char *)s)[idx] != '\0')
	{
		copy_str[idx] = ((char *)s)[idx];
		idx++;
	}
	copy_str[idx] = '\0';
	return (copy_str);
}