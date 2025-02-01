/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:44:50 by jahong            #+#    #+#             */
/*   Updated: 2025/01/31 18:57:16 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_only_wildcard_token(t_list *node)
{
	int		result;
	int		cnt;

	cnt = count_list_current_directory();
	if (cnt == -1)
		return (cnt);
	result = open_n_read_current_filenames(node, cnt);
	return (result);
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

int	change_partial_wildcard1(t_list *node, char *str)
{
//	char	**tmp;
	int		cnt;
	int		result;
	
	printf("after contion jump copy str = %s\n", str);
	// if (str == NULL)
	// 	return (-1);
	cnt = count_list_current_directory();
	if (cnt == -1)
		return (cnt);
	result = open_n_filter_current_filenames(node, str, cnt);
	if (result == -1)
		return (-1);
	return (1);
}