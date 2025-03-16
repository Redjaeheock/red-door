/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclusive_use_wildcard_join.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:58:53 by jahong            #+#    #+#             */
/*   Updated: 2025/02/13 17:39:08 by jahong           ###   ########.fr       */
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
		if (check_chr_not_quote_set(paths[row], '*') != 0)
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

char	*exclusive_use_wildcard_join2(char **paths, int *row)
{
	char	*keep1;
	char	*keep2;

	keep1 = NULL;
	while (paths[*row] != NULL)
	{
		if (check_chr_not_quote_set(paths[*row], '*') != 0)
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
		if (check_chr_not_quote_set(paths[row], '*') == 0)
			keep = exclusive_use_wildcard_join2(paths, &row);
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
