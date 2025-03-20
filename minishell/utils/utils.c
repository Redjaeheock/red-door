/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:50 by jahong            #+#    #+#             */
/*   Updated: 2025/03/20 16:26:06 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_null_string(void)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (memory_alloc_error());
	tmp[0] = '\0';
	return (tmp);
}

int	check_chr_not_quote_set(char *str, char c)
{
	int		idx;
	int		quote;

	idx = 0;
	quote = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '"' || str[idx] == '\'')
			quote = check_quote_pair(str[idx], quote);
		if (quote == 0 && str[idx] == '*')
			return (1);
		idx++;
	}
	return (0);
}

int	search_chr_in_str(char *str, char c)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == c)
		{
			flag = 1;
			break ;
		}
		idx++;
	}
	return (flag);
}

int	are_all_characters_same(char *str, char c)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 1;
	while (str[idx] != '\0')
	{
		if (str[idx] != c)
		{
			flag = 0;
			break ;
		}
		idx++;
	}
	return (flag);
}

char	**modify_least_matched_pattern(char **f_list, char *memo)
{
	char	**modify;
	int		len;
	int		idx;
	int		row;

	len = conditional_jump_len(memo, '1');
	modify = (char **)malloc(sizeof(char *) * (len + 1));
	if (modify == NULL)
		return (NULL);
	row = 0;
	idx = 0;
	while (f_list[row] != NULL)
	{
		if (memo[row] == '1')
		{
			modify[idx] = ft_strdup(f_list[row]);
			if (modify[idx] == NULL)
				return (sndry_alloc_err((void **)modify));
			idx++;
		}
		row++;
	}
	modify[idx] = NULL;
	return (modify);
}
