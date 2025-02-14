/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:13:00 by jahong            #+#    #+#             */
/*   Updated: 2025/02/06 13:45:05 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_path(t_path *path)
{
	char	**paths;

	while ((path != NULL) && (ft_strcmp(path->key, "PATH") != 0))
		path = path->next;
	paths = ft_split(path->value, ':');
	if (paths == NULL)
		return (memory_alloc_error());
	return (paths);
}

char	*extract_from_envp(char *envp, int *idx, char condition)
{
	char	*str;
	int		col;
	int		len;

	col = 0;
	len = conditional_strlen(envp, condition);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while ((envp[*idx] != condition) && (envp[*idx] != '\0'))
	{
		str[col] = envp[*idx];
		*idx += 1;
		col++;
	}
	if (envp[*idx] != '\0')
		*idx += 1;
	str[col] = '\0';
	return (str);
}

int	extract_key_value(t_path *tmp, char *envp)
{
	int	idx;
	int start;

	idx = 0;
	start = idx;
	tmp->key = extract_from_envp(envp, &idx, '=');
	tmp->value = extract_from_envp(envp, &idx, '\0');
	tmp->set = extract_from_envp(envp, &start, '\0');
	if (tmp->key == NULL || tmp->value == NULL || tmp->set == NULL)
		return (0);
	return (1);
}

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
	if (word_line == NULL)
		return (memory_alloc_error());
	while (idx < len && str[start_index + idx] != '\0')
	{
		word_line[idx] = str[start_index + idx];
		idx++;
	}
	word_line[idx] = '\0';
	return (word_line);
}