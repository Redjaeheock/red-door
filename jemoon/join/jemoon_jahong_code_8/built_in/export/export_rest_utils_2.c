/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_rest_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:57:15 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 16:59:05 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

char	**string_to_two_array(char *arr)
{
	char	**two_arr;

	two_arr = (char **)malloc(sizeof(char *) * (2));
	if (two_arr == NULL)
		return (memory_alloc_error());
	two_arr[0] = ft_strdup(arr);
	if (two_arr[0] == NULL)
		return (memory_alloc_error());
	two_arr[1] = NULL;
	return (two_arr);
}

void	*path_set(t_data *meta, char *str)
{
	char	**two_arr;
	char	**temp;

	two_arr = string_to_two_array(str);
	if (two_arr == NULL)
		return (memory_alloc_error());
	temp = ft_merge_2d_arr(meta->envm, two_arr);
	if (temp == NULL)
	{
		two_arr = free_sndry_arr((void **)two_arr);
		return (memory_alloc_error());
	}
	two_arr = free_sndry_arr((void **)two_arr);
	meta->envm = free_sndry_arr((void **)meta->envm);
	meta->envm = temp;
}

void	meta_path_set(t_data *meta, t_path *env_add)
{
	if (ft_strcmp(env_add->key, "PATH") == 0)
	{
		free_sndry_arr((void **)meta->path);
		meta->path = NULL;
		meta->path = extract_path(env_add);
		if (meta->path == NULL)
			memory_alloc_error();
		path_set(meta, env_add->set);
	}
	if (ft_strcmp(env_add->key, "HOME") == 0)
	{
		free(meta->home);
		meta->home = NULL;
		meta->home = search_value_using_key(env_add, "HOME");
		if (meta->home == NULL)
			memory_alloc_error();
	}
}
