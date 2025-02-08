/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclusive_use_wildcard_substitute2.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by jahong            #+#    #+#             */
/*   Updated: 2025/02/07 19:25:30 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exclusive_use_wildcard_valid_check(char *path)
{
	int	idx;
	int	quote;

	idx = 0;
	quote = 0;
	while (path[idx] != '\0')
	{
		quote = check_quote_pair(path[idx], quote);
		if (path[idx] == '*' && quote == 0)
			return (1);
		idx++;
	}
	return (0);
}

int	exclusive_use_wildcard_join_len(char **paths)
{
	int	row;
	int	cnt;
	int	flag;

	row = 0;
	cnt = 0;
	flag = 0;
	while (paths[row] != NULL)
	{
		if (exclusive_use_wildcard_valid_check(paths[row]) == 1)
		{
			cnt++;
			flag = 0;
		}
		else
		{
			if (flag == 0)
			{
				cnt++;
				flag = 1;
			}
		}
		row++;
	}
	return (cnt);
}

char	*exclusive_use_wildcar_join2(char **paths, int *row)
{
	char	*keep1;
	char	*keep2;

	keep1 = NULL;
	while (paths[*row] != NULL)
	{
		if (search_chr_in_str(paths[*row], '*') == 1)
			break ;
		keep2 = ft_strjoin_v2(keep1, paths[*row]);
		if (keep1 != NULL)
			free(keep1);
		if (keep2 == NULL)
			return (NULL);
		keep1 = keep2;
		*row += 1;
	}
	*row -= 1;
	return (keep1);
}

char	**exclusive_use_wildcard_join1(char **paths, int len)
{
	char	**join;
	char	*keep;
	int		row;
	int		n;

	join = (char **)malloc(sizeof(char *) * (len + 1));
	if (join == NULL)
		return (memory_alloc_error());
	n = 0;
	row = 0;
	while (paths[row] != NULL)
	{
		if (search_chr_in_str(paths[row], '*') == 0)
			keep = exclusive_use_wildcar_join2(paths, &row);
		else
			keep = ft_strdup(paths[row]);
		if (keep == NULL)
			return(free_multi_2d_arrs((void **)paths, (void **)join));
		join[n] = keep;
		n++;
		row++;
	}
	join[n] = NULL;
	free_sndry_arr((void **)paths);
	return (join);
}

char	**exclusive_use_wildcard_split1(char *src, int len, int row, int idx)
{
	char	**str;
	int		quote;
	int		start;

	start = 0;
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	quote = 0;
	while (src[idx] != '\0' && row < len)
	{
		if (src[idx] != '/' || (quote != 0 && src[idx] == '/'))
		{
			while (src[idx] != '\0')
			{
				if (src[idx] == '"' || src[idx] == '\'')
				{
					quote = check_quote_pair(src[idx], quote);
					if (quote != 0 && idx != 0 && src[idx - 1] == '*')
						break ;

				}
				if (quote == 0 && src[idx] == '/')
					break ;
				idx++;
			}
		}
		else
		{
			while (src[idx] == '/' && src[idx] != '\0')
				idx++;
		}
		str[row] = copy_index_range(src, start, idx);
		if (str[row] == NULL)
			return (NULL);
		start = idx;
		if (src[idx] == '"' && (quote == 0 || quote == 2))
			idx++;
		else if (src[idx] == '\'' && (quote == 0 || quote == 1))
			idx++;
		row++;
	}
	str[row] = NULL;
	return (str);
}

int	exclusive_use_wildcard_len(char *str)
{
	int	idx;
	int	cnt;
	int	quote;

	idx = 0;
	cnt = 0;
	quote = 0;
	while (str[idx] != 0)
	{
		if (str[idx] != '/' || (quote != 0 && str[idx] == '/'))
		{
			cnt++;
			while (str[idx] != '\0')
			{
				if (str[idx] == '"' || str[idx] == '\'')
				{
					quote = check_quote_pair(str[idx], quote);
					if (quote != 0 && idx != 0 && str[idx - 1] == '*')
					{
						idx++;
						break ;
					}
				}
				if (quote == 0 && str[idx] == '/')
					break ;
				idx++;
			}
		}
		else
		{
			cnt++;
			while (str[idx] == '/' && str[idx] != '\0')
				idx++;
		}
			
	}
	return (cnt);
}
