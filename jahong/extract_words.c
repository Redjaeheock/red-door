/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:13:00 by jahong            #+#    #+#             */
/*   Updated: 2025/01/09 19:58:15 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extrcat_path(char **envp, t_path *path)
{
	int	idx;
	int	cnt;

	idx = 0;
	cnt = 0;
	printf("visit\n");
	while (path != NULL && ft_strncmp(path->key, "PATH", 4) != 0)
		path = path->next;
	printf("search %s\n", path->value);
	while (path->value[idx] != '\0')
	{
		if (path->value[idx] == ':')
			cnt++;
		idx++;
	}
	printf("result cnt = %d\n", cnt);
	return (NULL);
}

char	*extract_from_envp(char *envp, int *idx, char condition)
{
	char	*str;
	int		col;
	int		len;

	col = 0;
	len = conditinal_strlen(envp, condition);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL /*리스트의 멤버 변수 free 작업 추가*/);
	while ((envp[*idx] != condition) && (envp[*idx] != '\0'))
	{
		str[col] = envp[*idx];
		*idx += 1;
		col++;
	}
	*idx += 1;
	str[col] = '\0';
	return (str);
}
int	extract_key_value(t_path *tmp, char *envp, int idx)
{
	int start;

	start = 0;
	tmp->key = extract_from_envp(envp, &idx, '=');
	tmp->value = extract_from_envp(envp, &idx, '\0');
	tmp->set = extract_from_envp(envp, &start, '\0');
	if ((tmp->key == NULL) || (tmp->key == NULL))
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