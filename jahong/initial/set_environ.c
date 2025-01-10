/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/01/10 12:37:34 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_path *make_t_path(void)
{
	t_path *tmp;

	tmp = (t_path *)malloc(sizeof(t_path));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->set = NULL;
	return (tmp);
}
t_path 	*init_key_value(char **envp)
{
	t_path	*env_path;
	t_path	*tmp;
	int		row;
	int		idx;

	row = 0;
	env_path = make_t_path();
	if (env_path == NULL)
		return (NULL);
	tmp = env_path;
	while (envp[row] != NULL)
	{
		idx = 0;
		if (extract_key_value(tmp, envp[row], idx) != 1)
			return (t_path_key_val_alloc_err(env_path));
		row++;
		if (envp[row] == NULL)
			break ;
		tmp->next = make_t_path();
		if (tmp->next == NULL)
			return (t_path_key_val_alloc_err(env_path));
		tmp = tmp->next;
	}
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
		return (sndry_alloc_err(NULL));
	idx = 0;
	while (envp[idx] != NULL)
	{
		cp_envp[idx] = ft_strdup(envp[idx]);
		if (cp_envp[idx] == NULL)
			return (sndry_alloc_err((void **)cp_envp));
		idx++;
	}
	cp_envp[idx] = NULL;
	return (cp_envp);
}
t_data	*initial_env(char **envp)
{
	t_data *meta;

	meta = (t_data *)malloc(sizeof(t_data) * 1);
	if (meta == NULL)
		return(t_data_alloc_err(NULL));
	meta->envm = NULL;
	meta->env = NULL;
	meta->exp = NULL;
	meta->path = NULL;
	meta->envm = copy_envp(envp);
	if (meta->envm == NULL)
		return (free_env_resource(meta));
	meta->env = init_key_value(envp);
	if (meta->env == NULL)
		return (free_env_resource(meta));
	meta->exp = init_key_value(envp);
	if (meta->exp == NULL)
		return (free_env_resource(meta));
	meta->path = extract_path(envp, meta->env);
	if (meta->path == NULL)
		return (free_env_resource(meta));
	return (meta);
}
