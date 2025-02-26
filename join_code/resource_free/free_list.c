/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:36:52 by jahong            #+#    #+#             */
/*   Updated: 2025/02/26 11:09:29 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_t_path(t_path	*path)
{
	t_path	*tmp;

	while (path != NULL)
	{
		tmp = path;
		path = path->next;
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->set != NULL)
			free(tmp->set);
		free(tmp);
	}
	return (NULL);
}

void	*free_t_list(t_list *node)
{
	t_list	*temp;

	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (node != NULL)
			node->prev = NULL;
		if (temp->f_list != NULL)
			free_sndry_arr((void **)temp->f_list);
		if (temp->token != NULL)
			free(temp->token);
		if (temp->key != NULL)
			free(temp->key);
		free(temp);
	}
	return (NULL);
}

void	*free_t_data(t_data *meta)
{
	if (meta == NULL)
		return (NULL);
	free(meta);
	return (NULL);
}

void	*free_meta_token(t_data *meta)
{
	if (meta->lval != NULL)
		free(meta->lval);
	if (meta->pid_n != NULL)
		free(meta->pid_n);
	if (meta->exit_n != NULL)
		free(meta->exit_n);
	if (meta->home != NULL)
		free(meta->home);
	if (meta->pwd != NULL)
		free(meta->pwd);
	if (meta->oldpwd != NULL)
		free(meta->oldpwd);
	if (meta->path != NULL)
		free_sndry_arr((void **)meta->path);
	if (meta->exp != NULL)
		free_t_path(meta->exp);
	if (meta->env != NULL)
		free_t_path(meta->env);
	if (meta->envm != NULL)
		free_sndry_arr((void **)meta->envm);
	if (meta->tokens != NULL)
		free_t_list(meta->tokens);
	if (meta->exec_cmd != NULL)
		free_exec_linked_list(meta->exec_cmd);
	if (meta != NULL)
		free_t_data(meta);
	return (NULL);
}
