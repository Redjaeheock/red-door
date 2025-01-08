/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_to_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:38:05 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/08 19:17:32 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_size(t_list **tmp, int *array_size)
{
	t_list	*tmp2;

	tmp2 = *tmp;
	if (REDIRECTION <= (*tmp)->type && (*tmp)->type <= HEREDOC)
	{
		*tmp = (*tmp)->next;
		(*array_size)++;
		if ((*tmp)->type == ARG)
		{
			*tmp = tmp2;
			++(*array_size);
			return (0);
		}
	}
	return (1);
}

int	get_double_string_array_size(t_list **tmp)
{
	t_list	*tmp2;
	int		array_size;

	tmp2 = *tmp;
	array_size = 0;
	if (check_redirection_size(&(*tmp), &array_size) == 0)
		return (array_size);
	while ((*tmp))
	{
		if ((*tmp)->type == PIPE)
		{
			array_size++;
			break ;
		}
		else if (REDIRECTION <= (*tmp)->type && (*tmp)->type <= HEREDOC)
			break ;
		*tmp = (*tmp)->next;
		array_size++;
	}
	*tmp = tmp2;
	return (array_size);
}

int	get_double_string_array_size_version_2(t_list **tmp)
{
	t_list	*tmp2;
	int		array_size;

	tmp2 = *tmp;
	array_size = 0;
	if ((*tmp)->type == PIPE)
		*tmp = (*tmp)->next;
	if (check_redirection_size(&(*tmp), &array_size) == 0)
		return (array_size);
	while ((*tmp))
	{
		if ((*tmp)->type == PIPE)
		{
			array_size++;
			break ;
		}
		else if (REDIRECTION <= (*tmp)->type && (*tmp)->type <= HEREDOC)
			break ;
		*tmp = (*tmp)->next;
		array_size++;
	}
	*tmp = tmp2;
	return (array_size);
}
