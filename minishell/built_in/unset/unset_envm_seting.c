/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_envm_seting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:36:30 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/17 16:04:16 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	key_check(char *envp)
{
	char	*key;
	int		i;

	i = 0;
	key = extract_from_envp(envp, &i, '=');
	if (key == NULL)
		return (0);
	if (ft_strcmp(key, "PATH") == 0)
	{
		free(key);
		key = NULL;
		return (0);
	}
	free(key);
	key = NULL;
	return (1);
}

int	sndry_arr_len_skip_path(void **array)
{
	int	len;
	int	j;

	j = 0;
	len = 0;
	if (array == NULL)
		return (0);
	while (array[len] != NULL)
	{
		if (key_check((char *)array[len]) == 0)
			j++;
		len++;
	}
	return (len - j);
}

char	**copy_envp_skip_path(char **envp)
{
	char	**cp_envp;
	int		idx;
	int		len;
	int		jdx;

	len = sndry_arr_len_skip_path((void **)envp);
	cp_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (cp_envp == NULL)
		return (sndry_alloc_err(NULL));
	idx = 0;
	jdx = 0;
	while (envp[idx] != NULL)
	{
		if (key_check(envp[idx]) != 0)
		{
			cp_envp[jdx] = ft_strdup(envp[idx]);
			if (cp_envp[jdx] == NULL)
				return (sndry_alloc_err((void **)cp_envp));
			jdx++;
		}
		idx++;
	}
	cp_envp[jdx] = NULL;
	return (cp_envp);
}

void	resize_meta_envm(t_data *meta)
{
	char	**skip_path;

	skip_path = copy_envp_skip_path(meta->envm);
	if (skip_path == NULL)
		return ;
	meta->envm = free_sndry_arr((void **)meta->envm);
	meta->envm = skip_path;
}
