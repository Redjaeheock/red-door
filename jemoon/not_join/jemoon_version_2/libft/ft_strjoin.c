/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:50:05 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/02 12:47:23 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_s2_len;
	char	*arr;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	s1_s2_len = ft_strlen(s1) + ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (s1_s2_len + 1));
	if (arr == NULL)
		return (s1);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
		arr[i++] = s2[j++];
	arr[i] = '\0';
	free(s1);
	return (arr);
}
