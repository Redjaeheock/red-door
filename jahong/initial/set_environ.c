/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/01/08 15:24:56 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	conditinal_strlen(const char *s, char condition)
{
	int	idx;

	idx = 0;
	if (s == NULL)
		return (0);
	while ((s[idx] != condition) && (s[idx] != '\0'))
		idx++;
	return (idx);
}

t_path 	*init_key_value(char **envp)
{
	t_path	*env_path;
	t_path	*tmp;
	int		idx;
	int		cyc;
	int		len;
	int		lol;

	idx = 0;
	env_path = (t_path *)malloc(sizeof(t_path));
	if (env_path == NULL)
		return (NULL);
	env_path->next = NULL;
	tmp = env_path;
	while (envp[idx] != NULL)
	{
		len = conditinal_strlen(envp[idx], '=');
		tmp->key = (char *)malloc(sizeof(char *) * len);
		if (tmp->key == NULL)
			free(env_path); // 구조체 배열 및 멤버 변수 free 확인
		cyc = 0;
		while(envp[idx][cyc] != '=')
		{
			tmp->key[cyc] = envp[idx][cyc];
			cyc++;
		}
		tmp->key[cyc] = '\0';
		cyc++;
		len = conditinal_strlen(&envp[idx][cyc], '\0');
		tmp->value = (char *)malloc(sizeof(char *) * len);
		if (tmp->value == NULL)
			free(env_path); // 구조체 배열 및 멤버	 변수 free 확인
		lol = 0;
		while (envp[idx][cyc] != '\0')
		{
			tmp->value[lol] = envp[idx][cyc];
			cyc++;
			lol++;
		}
		tmp->value[lol] = '\0';
		idx++;
		tmp->next = (t_path *)malloc(sizeof(t_path));
		tmp = tmp->next;
		if (tmp == NULL)
			free(env_path);
		tmp->next = NULL;
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
	t_path *tmp;

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
	tmp = meta->env;
	while (tmp->next != NULL)
	{
		printf("key = %s\n", tmp->key);
		printf("value = %s\n", tmp->value);
		tmp = tmp->next;
	}
	meta->exp = init_key_value(envp);
		return ((free_sndry_arr((void **)meta->envm), free_t_path(meta->env), free(meta), NULL));
//	meta->path = extrcat_path(envp);
//		return ((secondary_array_free(meta->envm), free_t_path(meta->env), free_t_path(meta->exp), free(meta), NULL));
	return (meta);
}