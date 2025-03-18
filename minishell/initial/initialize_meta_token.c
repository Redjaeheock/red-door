/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_meta_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:18:58 by jahong            #+#    #+#             */
/*   Updated: 2025/03/18 15:26:15 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_path	*make_t_path(void)
{
	t_path	*tmp;

	tmp = (t_path *)malloc(sizeof(t_path));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->set = NULL;
	return (tmp);
}

void	meta_token_init_memvar(t_data *meta)
{
	meta->oldstdin = -1;
	meta->oldstdout = -1;
	meta->oldstderr = -1;
	meta->heredoc = 0;
	meta->stdin_flag = 0;
	meta->pids = 0;
	meta->ppid = 0;
	meta->last_pid = 0;
	meta->tokens = NULL;
	meta->exec_cmd = NULL;
	meta->exp = NULL;
	meta->env = NULL;
	meta->envm = NULL;
	meta->path = NULL;
	meta->home = NULL;
	meta->pwd = NULL;
	meta->oldpwd = NULL;
}

int	initial_meta_basic_members(t_data *meta, char **envp)
{
	meta_token_init_memvar(meta);
	meta->ppid = get_ppid(meta);
	if (meta->ppid == -1)
		return ((free_meta_token(meta), 0));
	meta->envm = copy_envp(envp);
	if (meta->envm == NULL)
		return ((free_meta_token(meta), 0));
	meta->env = init_key_value(envp);
	if (meta->env == NULL)
		return ((free_meta_token(meta), 0));
	meta->exp = init_key_value(envp);
	if (meta->exp == NULL)
		return ((free_meta_token(meta), 0));
	return (1);
}

t_data	*initialize_meta_token(char **envp)
{
	t_data	*meta;

	meta = (t_data *)malloc(sizeof(t_data) * 1);
	if (meta == NULL)
		return ((memory_alloc_error(), NULL));
	if (initial_meta_basic_members(meta, envp) == 0)
		return (NULL);
	meta->home = search_value_using_key(meta->exp, "HOME");
	if (meta->home == NULL)
		return (free_meta_token(meta));
	meta->pwd = search_value_using_key(meta->exp, "PWD");
	if (meta->pwd == NULL)
		return (free_meta_token(meta));
	meta->oldpwd = initialize_oldpwd(meta->exp);
	if (meta->oldpwd == NULL)
		return (free_meta_token(meta));
	meta->path = extract_path(meta->env);
	if (meta->path == NULL)
		return (free_meta_token(meta));
	set_up_signal(meta);
	return (meta);
}
