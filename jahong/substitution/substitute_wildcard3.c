/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/02/04 11:23:41 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**mapping_pattern_start_filname(char **f_list, char *keep)
{
	char	**save;
	char	*str;
	int		row;
	int		n;
	int		len;

	row = 0;
	n = 0;
	len = count_valid_head_pattern_filename(f_list, keep);
	save = (char **)malloc(sizeof(char *) * (len + 1));
	if (save == NULL)
		return (memory_alloc_error());
	while (f_list[row] != NULL)
	{
		if (ft_str_head_str(f_list[row], keep) != NULL)
		{
			save[n] = ft_strdup(f_list[row]);
			if (save[n] == NULL)
				return (sndry_alloc_err((void **)save));
			n++;
		}
		row++;
	}
	save[n] = NULL;
	return (save);
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


char	**exclusive_use_wildcard_split(t_list *node, int len)
{
	char	**str;
	int		idx;
	int		start;
	int		quote;
	int		row;

	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (str == NULL)
		return (NULL);
	idx = 0;
	quote = 0;
	row = 0;
	while (node->token[idx] != '\0' && row < len)
	{
		if (node->token[idx] != '*')
		{
			start = idx;
			while (node->token[idx] != '\0')
			{
				if (node->token[idx] == '\'' || node->token[idx] == '"')
					quote = check_quote_pair(node->token[idx], quote);
				if (quote == 0 && node->token[idx] == '*')
					break;
				idx++;
			}
		}
		else
		{
			start = idx;
			while (node->token[idx] == '*' && node->token[idx] != '\0')
				idx++;
		}
		printf("start = %d idx = %d\n", start, idx);
		str[row] = copy_index_range_jump_quote(node->token, start, idx);
		if (str[row] == NULL)
			return (free_sndry_arr((void **)str));
		row++;
	}
	str[row] = NULL;
	return (str);
}

char	**get_root_filelist(void)
{
	char	**f_list;
	int		len;

	len = count_file_in_directory("/");
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames("/", len);
	return (f_list);
}

char	**get_path_filelist(char *path)
{
	char	**f_list;
	int		len;
	len = count_file_in_directory(path);
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames(path, len);
	return (f_list);
}

char	**divide_path_n_pattern(char *str, int idx)
{
	char	**f_list;
	char	*keep;
	keep = copy_index_range(str, 0, idx + 1);
	if (keep == NULL)
		return (NULL);
	f_list = get_path_filelist(keep);
	free(keep);
	if (f_list == NULL || ft_strcmp(f_list[0], "no such path") == 0)
		return (f_list);
	keep = copy_index_range(str, idx + 1, ft_strlen(str));
	// if (keep == NULL)
	// 	return (NULL);
	// f_list = mapping_pattern_start_filname(f_list, keep);
	free(keep);
	return (f_list);
}

char	**open_root_directory(char **str, int row, int idx)
{
	char	**f_list;

	if (ft_strlen(str[row]) == 1)
		f_list = get_root_filelist();
	else if (idx != 0 && ft_strlen(str[row]) - 1 == idx)
		f_list = get_path_filelist(str[row]);
	else if (idx == 0 || ft_strlen(str[row]) - 1 != idx)
	{
		if (str[row + 1] == NULL)
			f_list = get_path_filelist(str[row]);
		else
			f_list = divide_path_n_pattern(str[row], idx);
	}
	return (f_list);
}

char	**open_multi_directory(char **str, char **path, int row, int idx)
{
	char 	**f_list;
	char	*join;
	int		result;

	if (idx != 0 || ft_strlen(str[row]) - 1 == idx)
	{
		f_list = ft_add_str_to_2d_arr(path, str[row]);
		if (f_list == NULL)
			return (memory_alloc_error());
	}
	else if (ft_strlen(str[row]) - 1 != idx)
	{
		if (str[row + 1] == NULL)
			f_list = get_path_filelist(str[row]);
		else
			f_list = divide_path_n_pattern(str[row], idx);
	}
	return (f_list);
}

char	**file_open_preprocess(t_list *node, char **str, char **path, int row)
{
	char	**f_list;
	int		slash;
	int		result;
	int	idx = 0;

	slash = reverse_conditiona_strlen(str[row], '/');
	if (row == 0)
	{
		if (str[row][0] == '/')
			f_list = open_root_directory(str, row, slash);
		// else if (str[row][0] == '*')
		// 	result = open_current_directory(str, &tmp, row, slash);
		// else
		// 	result = open_path_directory(str, &tmp, row, slash);
		if (f_list == NULL || ft_strcmp(f_list[0], "no such path") == 0)
			return (f_list);
		while (f_list[idx] != NULL)
		{
			printf("get_file_list = %s\n", f_list[idx]);
			idx++;
		}
	}
	else
	{
		f_list = open_multi_directory(str, path, row, slash); //
		if (path != NULL)
			free(path);
	}
	return (f_list);
}


int	try_substitute_wildcard(t_list *node, int len)
{
	char	**str;
	char	**keep;
	int		row;

	row = 0;
	keep = NULL;
	str = exclusive_use_wildcard_split(node, len);
	if (str == NULL)
		return (-1);
	while (str[row] != NULL)
	{
		printf("aaaaa split exclusive wildcart str = %s\n", str[row]);
		row++;
	}
	row = 0;
	while (str[row] != NULL)
	{
		printf("split exclusive wildcart str = %s\n", str[row]);
		if (row != 0 && str[row][0] == '*')
		{
			row++;
			continue ;
		}
		keep = file_open_preprocess(node, str, keep, row);
		if (ft_strcmp(keep[0], "no such path") == 0)
		{
			printf("return here\n");
			return((free_sndry_arr((void **)keep), free_sndry_arr((void **)str), 0));
		}
		else if (keep == NULL)
			return (free_sndry_arr((void **)str), -1);
		row++;
	}
	return ((free_sndry_arr((void **)keep), free_sndry_arr((void **)str), 0));
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
		if (str[idx] != '*')
		{
			cnt++;
			while (str[idx] != '\0')
			{
				if (str[idx] == '\'' || str[idx] == '"')
					quote = check_quote_pair(str[idx], quote);
				if (quote == 0 && str[idx] == '*')
					break;
				idx++;
			}
		}
		else
		{
			cnt++;
			while (str[idx] == '*' && str[idx] != '\0')
				idx++;
		}
	}
	return (cnt);
}
int	substitute_wildcard(t_list *node)
{
	int		var;

	// var = checK_valid_wildcard_in_token(node);
	// if (var == 0)
	// 	return (1);
	if (node->token == NULL)
		return (0);
	var = exclusive_use_wildcard_len(node->token);
	printf("1 var = %d\n", var);
	if (var == 1 && node->token[0] != '*')
		return (0);
	if (var == 1 && node->token[0] == '*')
		return (change_only_wildcard_token(node));
	var = try_substitute_wildcard(node, var);
	// if (var == -1)
	// 	return (0);



	
	return (var);
}