/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 18:46:23 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	finishing_touches_f_list(t_list *node)
{
	if (node->f_list == NULL)
		return (0);
	if (node->f_list[0] == NULL)
	{
		node->f_list = free_sndry_arr((void **)node->f_list);
		return (0);
	}
	ft_sort_2d_arr(node->f_list);
	return (1);
}

char	**file_open_preprocess(char **path, char **f_list, int row)
{
	char	**keep;
	char	**tmp;
	int		len;

	len = sndry_arr_len((void **)path);
	if (row == 0)
	{
		if (path[row][0] == '/')
			keep = open_root_directory(path[row], len);
		else if (search_chr_in_str(path[row], '*') == 1)
			keep = open_wildcard_directory(path[row]);
		else
			keep = open_current_directory(path[row]);
	}
	else if (path[row][0] == '/')
	{
		keep = ft_add_str_to_2d_arr(f_list, path[row]);
		tmp = keep;
		keep = open_path_low_rank(tmp);
		free_sndry_arr((void **)tmp);
	}
	else
		keep = open_multi_directory(path[row], f_list);
	return (keep);
}

int	try_substitute_wildcard(t_list *node, char **paths)
{
	char	**keep1;
	char	**keep2;
	int		row;

	row = 0;
	keep1 = NULL;
	while (paths[row] != NULL)
	{
		if (row != 0 && are_all_characters_same(paths[row], '*') == 1)
		{
			row++;
			continue ;
		}
		keep2 = file_open_preprocess(paths, keep1, row);
		free_sndry_arr((void **)keep1);
		if (keep2 == NULL)
			return (-1);
		if (ft_strcmp(keep2[0], "Not_valid_path") == 0)
			return (free_sndry_arr((void **)keep2), 0);
		keep1 = keep2;
		row++;
	}
	node->f_list = keep1;
	return (1);
}

int	substitute_wildcard(t_list *node)
{
	char	**paths;
	int		var;

	if (node->token == NULL)
		return (0);
	if (check_chr_not_quote_set(node->token, '*') == 0)
		return (0);
	var = exclusive_use_wildcard_len(node->token);
	if (var == 1 && are_all_characters_same(node->token, '*') == 1)
		return (change_only_wildcard_token(node));
	paths = exclusive_use_wildcard_split1(node->token, var, 0, 0);
	if (paths == NULL)
		return (0);
	var = exclusive_use_wildcard_join_len(paths);
	paths = exclusive_use_wildcard_join1(paths, var);
	if (paths == NULL)
		return (0);
	var = try_substitute_wildcard(node, paths);
	free_sndry_arr((void **)paths);
	if (var == -1)
		return (0);
	var = finishing_touches_f_list(node);
	return (1);
}
