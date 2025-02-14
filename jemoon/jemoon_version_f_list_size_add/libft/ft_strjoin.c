/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:50:05 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/14 14:34:48 by jemoon           ###   ########.fr       */
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

char	*ft_strjoin_front_slash(char *s1, char *s2)
{
	int		s1_s2_len;
	char	*arr;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	s1_s2_len = ft_strlen(s1) + ft_strlen(s2);
	if (ft_strlen(s1) == 1)
		arr = (char *)malloc(sizeof(char) * (s1_s2_len + 1));
	else
		arr = (char *)malloc(sizeof(char) * (s1_s2_len + 1 + 1));
	if (arr == NULL)
		return (s1);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	if (ft_strlen(s1) == 1)
		while (i < ft_strlen(s1) + ft_strlen(s2))
			arr[i++] = s2[j++];
	else
	{
		while (i < ft_strlen(s1) + ft_strlen(s2) + 1)
		{
			if (ft_strlen(s1) == i)
				arr[i++] = '/';
			else
				arr[i++] = s2[j++];
		}
	}
	arr[i] = '\0';
	free(s1);
	return (arr);
}
