/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/01/06 17:10:15 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_path 	*init_key_value(char **envp)
{
	t_path	*env_path;

	env_path = NULL;

	return (env_path);

}

char	**copy_envp(char **envp)
{
	char	**cp_envp;
	int		idx;
	int		len;

	len = sndry_arr_len((void **)envp);

	cp_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (cp_envp == NULL)
		return (NULL /* 에러 메시지*/);
	idx = 0;
	while (envp[idx] != NULL)
	{
		cp_envp[idx] = ft_strdup(envp[idx]);
		if (cp_envp[idx] == NULL)
			return (free_sndry_arr((void **)cp_envp));
		idx++;
	}
	cp_envp[idx] = NULL;
	return (cp_envp);
}

t_data	*initial_env(char **envp)
{
	t_data *meta;
	int		idx;

	idx = 0;
	meta = (t_data *)malloc(sizeof(t_data) * 1);
	if (meta == NULL)
		return(NULL /*에러 메세지 추가*/);
	
	meta->envm = copy_envp(envp);
	if (meta->envm == NULL)
		return ((free(meta), NULL));
	meta->env = init_key_value(envp);
	if (meta->env == NULL)
		return ((free_sndry_arr((void **)meta->envm), free(meta), NULL));
	meta->exp = init_key_value(envp);
		return ((free_sndry_arr((void **)meta->envm), free_t_path(meta->env), free(meta), NULL));
//	meta->path = extrcat_path(envp);
//		return ((secondary_array_free(meta->envm), free_t_path(meta->env), free_t_path(meta->exp), free(meta), NULL));
	return (meta);
}