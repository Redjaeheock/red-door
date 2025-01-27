/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:36:52 by jahong            #+#    #+#             */
/*   Updated: 2025/01/26 16:36:53 by jemoon           ###   ########.fr       */
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
		free(tmp);
	}
	return (NULL);
}
void	*free_key_value(t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (tmp != NULL)
	{
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->set != NULL)
			free(tmp->set);
		tmp = tmp->next;
	}
	return (NULL);
}
void	*free_t_list(t_list *list)
{
	t_list	*temp;

	// 구조체 멤버 해제 후 리스트 해제제

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		temp->prev = NULL;
		free(temp->token);
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

void	*free_env_resource(t_data *meta)
{
	if (meta->path != NULL)
		free(meta->path);
	if (meta->exp != NULL)
		free_key_value(meta->exp);
	if (meta->env != NULL)
		free_key_value(meta->env);
	if (meta->envm != NULL)
		free_sndry_arr((void **)meta->envm);
	if (meta != NULL)
		free_t_data(meta);
	return (NULL);
}
