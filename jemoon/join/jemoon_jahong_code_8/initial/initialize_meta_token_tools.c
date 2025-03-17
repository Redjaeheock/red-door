/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_meta_token_tools.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:10:43 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 19:27:48 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_underbar_path(t_path *path)
{
	t_path	*tmp;

	tmp = NULL;
	while (path->next != NULL)
	{
		if (strcmp(path->next->key, "_") == 0)
		{
			if (path->next->next != NULL)
			{
				tmp = path->next;
				path->next = path->next->next;
				tmp->next = NULL;
			}
		}
		path = path->next;
	}
	if (tmp != NULL)
		path->next = tmp;
}

t_path	*init_key_value(char **envp)
{
	t_path	*env_path;
	t_path	*tmp;
	int		row;

	row = 0;
	env_path = make_t_path();
	if (env_path == NULL)
		return (memory_alloc_error());
	tmp = env_path;
	while (envp[row] != NULL)
	{
		if (extract_key_value(tmp, envp[row]) != 1)
			return (t_path_key_val_alloc_err(env_path));
		row++;
		if (envp[row] == NULL)
			break ;
		tmp->next = make_t_path();
		if (tmp->next == NULL)
			return (t_path_key_val_alloc_err(env_path));
		tmp = tmp->next;
	}
	move_underbar_path(env_path);
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

static int	extract_ppid(char *buffer)
{
	char	*tmp;
	char	*end;

	tmp = ft_strnstr(buffer, "Pid:", ft_strlen(buffer));
	if (tmp == NULL)
		return (0);
	end = ft_strchr(tmp, '\n');
	if (end == NULL)
	{
		end = ft_strchr(tmp, '\0');
		if (end == NULL)
			return ((printf("bash: system error file EOF\n"), -1));
	}
	*end = '\0';
	while (ft_isdigit(*tmp) == 0 && *tmp != '\0')
		tmp++;
	if (*tmp == '\0')
		return (0);
	return (ft_atoi(tmp));
}

int	get_ppid(t_data *meta)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	buffer_size;
	int		fd;
	int		ppid;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((printf("bash: system error cannot such pid\n"), -1));
	while (1)
	{
		buffer_size = read(fd, buffer, BUFFER_SIZE - 1);
		if (buffer_size < 0)
			return ((close(fd), 0));
		buffer[buffer_size] = '\0';
		ppid = extract_ppid(buffer);
		if (ppid == -1)
			break ;
		if (ppid == 0)
			continue ;
		else
			return ((close(fd), ppid));
	}
	printf("bash: system error cannot such pid\n");
	return ((close(fd), -1));
}
