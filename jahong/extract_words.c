/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:13:00 by jahong            #+#    #+#             */
/*   Updated: 2025/01/02 11:00:12 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(char const *str, int start_index, int end)
{
	char	*word_line;
	int		idx;
    int     len;

	idx = 0;
    if (str == NULL)
        return (NULL);
    len = (end - start_index);
    word_line = (char *)malloc(sizeof(char) * (len + 1));
    if (!word_line)
		return (NULL);
	while (idx < len && str[start_index + idx] != '\0')
	{
		word_line[idx] = str[start_index + idx];
		idx++;
	}
	word_line[idx] = '\0';
	return (word_line);
}