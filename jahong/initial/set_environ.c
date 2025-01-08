/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/01/08 21:05:26 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	conditinal_strlen(const char *s, unsigned char condition)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while ((s[len] != condition) && (s[len] != '\0'))
		len++;
	return (len);
}

char	*extract_from_envp(char *envp, int *idx, char condition)
{
	char	*str;
	int		col;
	int		len;

	col = 0;
	len = conditinal_strlen(envp, condition);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL /*리스트의 멤버 변수 free 작업 추가*/);
	while ((envp[*idx] != condition) && (envp[*idx] != '\0'))
	{
		str[col] = envp[*idx];
		*idx += 1;
		col++;
	}
	*idx += 1;
	str[col] = '\0';
	return (str);
}

t_path 	*init_key_value(char **envp)
{
	t_path	*env_path;
	t_path	*tmp;
	int		row;
	int		idx;

	row = 0;
	env_path = (t_path *)malloc(sizeof(t_path));
	if (env_path == NULL)
		return (NULL);
	env_path->next = NULL;
	tmp = env_path;
	while (envp[row] != NULL)
	{
		idx = 0;
		tmp->key = extract_from_envp(envp[row], &idx, '=');
//		if (tmp->key == NULL)
//			free(env_path); // 구조체 리스트 free 확인
		tmp->value = extract_from_envp(envp[row], &idx, '\0');
//		if (tmp->value == NULL)
//			free(env_path); // 구조체 배열 및 멤버	 변수 free 확인
		row++;
		tmp->next = (t_path *)malloc(sizeof(t_path));
		if (tmp->next == NULL)
		{
			free(tmp);
			return (NULL);
		}
		tmp = tmp->next;
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
	/*while (envp[idx] != NULL)
	{
		printf("orgin %s\n", envp[idx]);
		idx++;
	}*/
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