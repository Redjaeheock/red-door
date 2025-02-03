/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:44:50 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 15:16:46 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_only_wildcard_token(t_list *node)
{
	char	**tmp;
	int		result;
	int		cnt;

	cnt = count_file_in_directory(".");
	if (cnt == -1)
		return (cnt);
	tmp = open_n_read_filenames(".", cnt);
	if (tmp == NULL)
		return (-1);
	node->f_list = tmp;
	return (1);
}

// int	change_partial_wildcard2(t_path *env, t_list *node, int	idx, int end)
// {
// 	char	**tmp;
// 	char	*str;
// 	int		cnt;
// 	int		result;
	
// 	// str = copy_conditional_index_range(node->token, idx, end, '"');
// 	// if (str == NULL)
// 	// 	return (-1);
// 	// cnt = count_list_current_directory();
// 	// if (cnt == -1)
// 	// {
// 	// 	free(str);
// 	// 	return (cnt);
// 	// }
// 	// result = open_n_read_filenames2(node, ".", str, cnt);
// 	// free(str);
// 	result  = 0;
// 	return (result);
// }

int	change_partial_wildcard1(t_list *node, char *pattrn)
{
//	char	**tmp;
	int		cnt;
	int		result;
	
	printf("after contion jump copy str = %s\n", pattrn);
	// if (str == NULL)
	// 	return (-1);
	cnt = count_file_in_directory(pattrn);
	if (cnt == -1)
		return (cnt);
	// result = open_n_filter_filenames(node, pattrn, cnt);
	// if (result == -1)
	// 	return (-1);
	// if (node->f_list[0] == NULL)
	// 	return (0);
	return (1);
}