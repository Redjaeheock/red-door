/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_as_file2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:28:40 by jahong            #+#    #+#             */
/*   Updated: 2025/02/14 14:25:20 by jahong           ###   ########.fr       */
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
	char	**keep;
	int		len;
	len = count_file_in_directory(path);
	if (len == -1)
		return (NULL);
	keep = open_n_read_filenames(path, len);
	f_list = ft_add_2d_arr_to_str(path, keep);
	free_sndry_arr((void **)keep);
	return (f_list);
}
