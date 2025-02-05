/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:20:44 by jahong            #+#    #+#             */
/*   Updated: 2025/02/06 00:18:56 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**modify_least_matched_pattern(char **f_list, char *memo)
{
	char	**modify;
	int		len;
	int		idx;
	int		row;

	len = conditional_jump_len(memo, '1');
	idx = 0;
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

int	compare_word(char *f_list, int idx, char **path, int *row)
{
	int	col;
	int	len;

	col = 0;
	len = ft_strlen(path[*row]);
	while ((f_list[idx] != '\0' && path[*row][col] != '\0'))
	{
		if (f_list[idx] == path[*row][col])
		{
			col++;
			idx++;
			if (col == len)
			{
				*row += 1;
				return (col - 1);
			}
		}
		else
		{
			idx += 1 - col;
			col = 0;
		}
	}
	return (ft_strlen(f_list));
}

int	matching_fisrt_pattern(char *f_list, char **path)
{
	int	row;
	int	idx;

	row = 0;
	idx = 0;
	if (f_list[0] != path[row][0])
		return (0);
	while (f_list[idx] != '\0')
	{
		idx = compare_word(f_list, idx, path, &row);
		if (idx == ft_strlen(f_list))
			return (0);
		if (row == sndry_arr_len((void **)path))
			break ;
		idx++;
	}
	if (idx == ft_strlen(f_list) && row != sndry_arr_len((void **)path))
		return (0);
	return (1);
}

char	**mapping_pattern_start_filname(char **path, char **f_list)
{
	char	**modify;
	char	*memo;
	int		row;
	int		result;
	int		len;

	len = sndry_arr_len((void **)f_list);
	memo = (char *)malloc(sizeof(char) * (len + 1));
	if (memo == NULL)
		return (memory_alloc_error());
	row = 0;
	while (f_list[row] != NULL)
	{
		result = matching_fisrt_pattern(f_list[row], path);
		memo[row] = result + 48;
		row++;
	}
	memo[row] = '\0';
	modify = modify_least_matched_pattern(f_list, memo);
	free(memo);
	return (modify);
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
int	exclusive_use_wildcard_jon_len(char **paths)
{
	int	row;
	int	cnt;
	int	flag;

	row = 0;
	cnt = 0;
	flag = 0;
	while (paths[row] != NULL)
	{
		if (search_chr_in_str(paths[row], '*') == 1)
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

char	**exclusive_use_wildcard_split(char *src, int len, int row, int idx)
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
		start = idx;
		if (src[idx] != '/')
		{
			while (src[idx] != '\0')
			{
				quote = check_quote_pair(src[idx], quote);
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
		str[row] = copy_index_range_jump_quote(src, start, idx);
		if (str[row] == NULL)
			return (NULL);
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

char	**get_current_filelist(void)
{
	char	**f_list;
	int		len;

	len = count_file_in_directory(".");
	if (len == -1)
		return (NULL);
	f_list = open_n_read_filenames(".", len);
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

// char	**divide_path_n_pattern(char *str, int idx)
// {
// 	char	**f_list;
// 	char	**keep;
// 	char	*copy;

// 	copy = copy_index_range(str, 0, idx + 1);
// 	if (copy == NULL)
// 		return (NULL);
// 	f_list = get_path_filelist(copy);
// 	free(copy);
// 	if (f_list == NULL || ft_strcmp(f_list[0], "Not valid path") == 0)
// 		return (f_list);
// 	keep = f_list;
// 	f_list = NULL;
// 	copy = copy_index_range(str, idx + 1, ft_strlen(str));
// 	if (copy == NULL)
// 		return (free_sndry_arr((void **)keep));
// 	f_list = mapping_pattern_start_filname(keep, copy);
// 	free(copy);
// 	free_sndry_arr((void **)keep);
// 	return (f_list);
// }

char	**open_root_directory(char *str)
{
	char	**f_list;

	if (ft_strlen(str) == 1)
		f_list = get_root_filelist();
	else
		f_list = get_path_filelist(str);
	return (f_list);
}

// char	**open_current_directory(char **str, int row, int idx)
// {
// 	char	**f_list;
// 	char	**keep;

// 	f_list = get_current_filelist();
// 	if (str[row][0] == '*' && str[row + 1] == NULL)
// 		return (f_list);
// 	else if (str[row + 1] != NULL)
// 	{
// 		if (search_chr_in_str(str[row + 1], '/') == 0)
// 		{
// 			keep = f_list;
// 			f_list = mapping_pattern_start_filname(keep, str[row]);

// 		}

// 	}
// 	return (NULL);

// }

char	**open_multi_directory(char *path, char **f_list)
{
	char 	**keep;
	char	**div;;
	int		result;
	int		len;

	len = ft_strlen(path);
	if (search_chr_in_str(path, '*') == 1)
	{
		div = ft_split(path, '*');
		if (div == NULL)
			return (NULL);
		if (path[0] != '*' && path[len - 1] == '*')
			keep = mapping_pattern_start_filname(div, f_list);
		// else if (str[0] == '*' && str[len - 1] != '*')

		// else if (str[0] != '*' && str[len - 1] != '*')

		// else if (str[0] == '*' && str[len - 1] == '*')
		free_sndry_arr((void **)div);
		if (keep == NULL)
			return (NULL);
	}
	return (keep);
}

char	**file_open_preprocess(char *path, char **f_list, int row)
{
	char	**keep;
	int		result;
	int	idx = 0;

	if (row == 0)
	{
		if (path[0] == '/')
			keep = open_root_directory(path);
		// else if (str[row][0] == '*')
		// 	f_list = open_current_directory(str, row, slash);
		// else
		// 	result = open_path_directory(str, &tmp, row, slash);
		while (keep[idx] != NULL)
		{
			printf("get_file_list = %s\n", keep[idx]);
			idx++;
		}
	}
	else
		keep = open_multi_directory(path, f_list); //
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
		keep2 = file_open_preprocess(paths[row], keep1, row);
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
		if (str[idx] != '/')
		{
			cnt++;
			while (str[idx] != '\0')
			{
				quote = check_quote_pair(str[idx], quote);
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
	// if (var == 1 && node->token[0] != '*')
	// 	return (0);
	if (var == 1 && node->token[0] == '*')
		return (change_only_wildcard_token(node));
	paths = exclusive_use_wildcard_split(node->token, var, 0, 0);
	if (paths == NULL)
		return (0);
	var = exclusive_use_wildcard_jon_len(paths);
	printf("join len = %d\n", var);
	paths = exclusive_use_wildcard_join1(paths, var);
	if (paths == NULL)
		return (0);
	while (paths[row] != NULL)
	{
		printf("jion after split paths str = %s\n", paths[row]);
		row++;
	}
	var = try_substitute_wildcard(node, paths);
	free_sndry_arr((void **)paths);
	// if (var == -1)
	// 	return (0);



	
	return (var);
}
