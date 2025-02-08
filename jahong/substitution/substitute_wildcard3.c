/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/02/08 11:26:12 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_only_single_chr_value_in_2d_arr(char **str, int row, char c)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[row] != NULL)
	{
		if (are_all_characters_same(str[row], c) == 0)
			len++;
		row++;
	}
	return (len);
}

char	**remove_all_same_str(char **str, char c)
{
	char	**keep;
	int		row;
	int		len;

	row = 0;
	len = count_only_single_chr_value_in_2d_arr(str, row, c);
	keep = (char **)malloc(sizeof(char *) * (len + 1));
	if (keep == NULL)
		return (memory_alloc_error());
	len = 0;
	while (str[row] != 0)
	{
		if (are_all_characters_same(str[row], c) == 0)
		{
			keep[len] = ft_strdup(str[row]);
			if (keep[len] == NULL)
				return (sndry_alloc_err((void **)keep));
			len++;
		}
		row++;
	}
	keep[len] = NULL;
	return (keep);
}

char	**take_pattern_in_path(char *path, char **div, int len, char c)
{
	int		row;
	int 	idx;
	int		quote;
	int		start;

	idx = 0;
	row = 0;
	quote = 0;
	start = idx;
	while (path[idx] != 0 && row < len)
	{
		if (path[idx] == c)
		{
			while (path[idx] == c && path[idx] != '\0')
				idx++;
		}
		else
		{
			while (path[idx] != '\0')
			{
				if (path[idx] == '\'' || path[idx] == '"')
					quote = check_quote_pair(path[idx], quote);
				if (quote == 0 && path[idx] == c)
					break;
				idx++;
			}
		}
		div[row] = copy_index_range_jump_quote(path, start, idx);
		if (div[row] == NULL)
			return (sndry_alloc_err((void **)div));
		start = idx;
		row++;
	}
	div[row] = NULL;
	return (div);
}

int	count_valid_split(char *path, char c)
{
	int	idx;
	int	cnt;
	int quote;

	idx = 0;
	cnt = 0;
	quote = 0;
	while (path[idx] != '\0')
	{
		if (path[idx] == c)
		{
			cnt++;
			while (path[idx] == c && path[idx] != '\0')
				idx++;
		}
		else
		{
			cnt++;
			while (path[idx] != '\0')
			{
				if (path[idx] == '\'' || path[idx] == '"')
					quote = check_quote_pair(path[idx], quote);
				if (quote == 0 && path[idx] == c)
					break;
				idx++;
			}
		}
	}
	return (cnt);
}

char	**quote_conitional_split(char *path, char c)
{
	char	**div;
	char	**keep;
	int		idx;
	int		len;

	idx = 0;
	len = count_valid_split(path, c);
	div = (char **)malloc(sizeof(char *) * (len + 1));
	if (div == NULL)
		return (memory_alloc_error());
	div = take_pattern_in_path(path, div, len, c);
	if (div == NULL)
		return (NULL);
	keep = div;
	div = remove_all_same_str(keep, c);
	free_sndry_arr((void **)keep);
	return (div);
}

int	check_valid_split(char *path, char c)
{
	char	**div;
	int		idx;
	int		quote;
	int		flag;

	idx = 0;
	quote = 0;
	flag = 0;
	while (path[idx] != '\0')
	{
		if (path[idx] == '"' || path[idx] == '\'')
			quote = check_quote_pair(path[idx], quote);
		if (quote == 0 && path[idx] == '*')
			flag = 1;
		idx++;
	}
	return (flag);
}


char	*copy_index_range_jump_quote(char *str, int idx, int end)
{
	char	*copy;
	int		len;
	int		n;

	n = 0;
	len = quote_set_jump_len(str);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (memory_alloc_error());
	while (idx < end)
	{
		if (str[idx] == '\'' || str[idx] == '"')
		{
			idx++;
			continue ;
		}
		copy[n] = str[idx];
		n++;
		idx++;
	}
	copy[n] = '\0';
	return (copy);
}

char	**open_multi_directory(char *path, char **f_list)
{
	char 	**keep;
	char	**div;
	char	*copy;
	int		result;
	int		len;
	int	row = 0;

	len = ft_strlen(path);
	if (check_valid_split(path, '*') == 1)
	{
		div = quote_conitional_split(path, '*');
		if (div == NULL)
			return (NULL);
		while (div[row] != NULL)
		{
			printf("div[%d] = %s\n", row, div[row]);
			row++;
		}
		if (path[0] != '*' && path[len - 1] == '*')
			keep = mapping_pattern_start_filname(div, f_list);
		else if (path[0] == '*' && path[len - 1] != '*')
			keep = mapping_pattern_last_filname(div, f_list);
		else if (path[0] != '*' && path[len - 1] != '*')
			keep = mapping_pattern_side_filname(div, f_list);
		else if (path[0] == '*' && path[len - 1] == '*')
			keep = mapping_center_filename(div, f_list);
		free_sndry_arr((void **)div);
	}
	else
	{
		printf("open_multi_drectory_els\n");
		copy = copy_index_range_jump_quote(path, 0, ft_strlen(path));
		if (copy == NULL)
			return (NULL);
		
		keep = mapping_pattern_filename(copy, f_list);
		free(copy);
	}
	return (keep);
}

char	**file_open_preprocess(char **path, char **f_list, int row)
{
	char	**keep;
	int		result;
	int		len;
	int	idx = 0;

	len = sndry_arr_len((void **)path);
	if (row == 0)
	{
		if (path[row][0] == '/')
			keep = open_root_directory(path[row], len);
		else if (search_chr_in_str(path[row], '*') == 1)
			keep = open_wildcard_directory(path[row]);
		else
			keep = open_current_directory(path[row]);
		while (keep[idx] != NULL)
		{
			printf("get_file_list = %s\n", keep[idx]);
			idx++;
		}
	}
	else
	{
		
		keep = open_multi_directory(path[row], f_list); //
	}
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
		printf("split exclusive wildcart str = %s\n", paths[row]);
		if (row != 0 && are_all_characters_same(paths[row], '*') == 1)
		{
			row++;
			continue ;
		}
		keep2 = file_open_preprocess(paths, keep1, row);
		free_sndry_arr((void **)keep1);
		if (keep2 == NULL)
			return (-1);
		if (ft_strcmp(keep2[0], "Not valid path") == 0)
			return(free_sndry_arr((void **)keep2), 0);
		keep1 = keep2;
		row++;
	}
	row = 0;
	printf("keep1 total len = %d\n", sndry_arr_len((void **)keep1));
	while (keep1[row] != NULL)
	{
		printf("keep in %d =  %s\n", row, keep1[row]);
		row++;
	}
	node->f_list = keep1;
	return (1);
}

int	substitute_wildcard(t_list *node)
{
	printf("try subtutite wildcart func\n");
	char	**paths;
	int		var;
	int	row = 0;

	if (node->token == NULL)
		return (0);
	var = exclusive_use_wildcard_len(node->token);
	printf("split len = %d\n", var);
	if (var == 1 && are_all_characters_same(node->token, '*') == 1)
		return (change_only_wildcard_token(node));
	paths = exclusive_use_wildcard_split1(node->token, var, 0, 0);
	if (paths == NULL)
		return (0);
	row = 0;
	while (paths[row] != NULL)
	{
		printf("split paths str = %s\n", paths[row]);
		row++;
	}
	printf("\n");
	var = exclusive_use_wildcard_join_len(paths);
	printf("join len = %d\n", var);
	paths = exclusive_use_wildcard_join1(paths, var);
	if (paths == NULL)
		return (0);
	row = 0;
	while (paths[row] != NULL)
	{
		printf("join after split paths str = %s\n", paths[row]);
		row++;
	}
	var = try_substitute_wildcard(node, paths);
	free_sndry_arr((void **)paths);
	row = 0;
	while (node->f_list != NULL && node->f_list[row] != NULL)
	{
		printf("filelist all show = %s\n", node->f_list[row]);
		row++;
	}
	// if (var == -1)
	// 	return (0);



	
	return (var);
}
