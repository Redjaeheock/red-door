/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commads_size_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:12:08 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 19:59:33 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	handle_redirection_case(t_list *tokens, int *check_redi, \
t_tokentype *plag_redi)
{
	(*check_redi) = 1;
	(*plag_redi) = tokens->type;
	if (tokens->f_list != NULL)
		return (sndry_arr_len((void **)tokens->f_list));
	return (1);
}

int	handle_pipe_case(t_list *tokens, t_tokentype *plag_pipe)
{
	(*plag_pipe) = tokens->type;
	if (tokens->f_list != NULL)
		return (sndry_arr_len((void **)tokens->f_list));
	return (1);
}

int	handle_previous_redirection(t_list *tokens, int *check_redi)
{
	(*check_redi) = 0;
	if (tokens->f_list != NULL)
		return (sndry_arr_len((void **)tokens->f_list));
	return (1);
}

int	calculate_array_size(t_list *tokens)
{
	int	array_size;

	array_size = 0;
	while (tokens && !(AND <= tokens->type && tokens->type <= HEREDOC))
	{
		if (tokens->f_list != NULL)
			array_size = array_size + sndry_arr_len((void **)tokens->f_list);
		else if (tokens->token != NULL)
			array_size++;
		tokens = tokens->next;
	}
	return (array_size);
}

int	get_double_string_array_size(t_list *tokens, int *check_redi, \
t_tokentype *plag_pipe, t_tokentype *plag_redi)
{
	if (REDIRECTION <= tokens->type && tokens->type <= HEREDOC)
	{
		return (handle_redirection_case(tokens, check_redi, plag_redi));
	}
	else if (AND <= tokens->type && tokens->type <= PIPE)
	{
		return (handle_pipe_case(tokens, plag_pipe));
	}
	else if (*check_redi == 1)
	{
		return (handle_previous_redirection(tokens, check_redi));
	}
	else
	{
		return (calculate_array_size(tokens));
	}
}
