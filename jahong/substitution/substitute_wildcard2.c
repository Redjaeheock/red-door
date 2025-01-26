/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_wildcard2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:44:50 by jahong            #+#    #+#             */
/*   Updated: 2025/01/26 16:45:25 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_only_wildcard_token(t_path *env, t_list *node)
{
	int		result;
	int		cnt;

	cnt = count_list_current_directory();
	if (cnt == -1)
		return (cnt);
	result = open_n_read_filenames1(node, ".", cnt);
	return (result);
}
int	change_partial_wildcard2(t_path *env, t_list *node, int	idx, int end)
{
	char	**tmp;
	char	*str;
	int		cnt;
	int		result;
	
	str = copy_index_range(node->token, idx, end);
	if (str == NULL)
		return (-1);
	cnt = count_list_current_directory();
	if (cnt == -1)
	{
		free(str);
		return (cnt);
	}
	result = open_n_read_filenames2(node, ".", str, cnt);
	free(str);
	return (result);
}
int	change_partial_wildcard1(t_path *env, t_list *node, int	idx, int end)
{
	char	**tmp;
	char	*str;
	int		cnt;
	int		result;
	
	str = copy_index_range(node->key, idx, end);
	if (str == NULL)
		return (-1);
	cnt = count_list_current_directory();
	if (cnt == -1)
	{
		free(str);
		return (cnt);
	}
	result = open_n_read_filenames2(node, ".", str, cnt);
	free(str);
	return (result);
}