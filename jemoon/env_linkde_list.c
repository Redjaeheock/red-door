/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linkde_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:24 by jemoon            #+#    #+#             */
/*   Updated: 2024/12/30 22:47:24 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*get_env_value(char *envp)
{
	int index;

	index = 0;
}

t_env_list	*create_env_liked_list(char *envp)
{
	t_env_list *new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (new == NULL)
		return (NULL);
	new->env_key;
	new->env_value;
	new->next = NULL;
	return (new);
}

void	make_env_node(t_env_list **env_list, char **envp)
{
	t_env_list	*new_node;
	int			index;

	index = 0;
	while (envp[index] != NULL)
	{
		new_node =  create_env_liked_list(envp[index]);
		if (new_node == NULL)
			return ;
		if (*env_list == NULL)
			*env_list = new_node;
		else
			add_back_env_linked_list(env_list, new_node);
		index++;
	}
}