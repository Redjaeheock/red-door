/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_size_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:12:08 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/21 11:26:47 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redirection_case(t_list *tokens, int *check_redi, \
t_tokentype *plag_redi)
{
	(*check_redi) = 1;
	(*plag_redi) = tokens->type;
	return (1);
}

int	handle_pipe_case(t_list *tokens, t_tokentype *plag_pipe)
{
	(*plag_pipe) = tokens->type;
	return (1);
}

int	handle_previous_redirection(int *check_redi)
{
	(*check_redi) = 0;
	return (1);
}

int	calculate_array_size(t_list *tokens)
{
	int	array_size;

	array_size = 0;
	while (tokens && !(AND <= tokens->type && tokens->type <= HEREDOC))
	{
		array_size++;
		tokens = tokens->next;
	}
	return (array_size);
}

