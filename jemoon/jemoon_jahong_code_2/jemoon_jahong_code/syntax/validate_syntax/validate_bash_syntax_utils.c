/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:35:17 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/18 17:04:34 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

int	check_is_valid_redirection(t_list **tokens)
{
	if ((*tokens)->next == NULL)
		return (0);
	else if (!(CMD <= (*tokens)->next->type && (*tokens)->next->type <= ARG))
		return (0);
	else
	{
		*tokens = (*tokens)->next;
		if (!(*tokens))
			return (1);
		*tokens = (*tokens)->next;
		return (1);
	}
}

int	check_is_valid_arg(t_list **tokens)
{
	*tokens = (*tokens)->next;
	while ((*tokens) != NULL)
	{
		if (AND <= (*tokens)->type && (*tokens)->type <= PIPE)
			return (1);
		else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
			return (1);
		else
			*tokens = (*tokens)->next;
	}
	return (1);
}

int	first_check_is_valid(t_list **tokens)
{
	if (AND <= (*tokens)->type && (*tokens)->type <= PIPE)
		return (0);
	else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
		return (check_is_valid_redirection(&(*tokens)));
	else if (CMD <= (*tokens)->type && (*tokens)->type <= ARG)
		return (check_is_valid_arg(&(*tokens)));
	else
		return (0);
}

int	rest_check_is_valid(t_list **tokens)
{
	if (AND <= (*tokens)->type && (*tokens)->type <= PIPE)
	{
		if ((*tokens)->prev && \
		(AND <= (*tokens)->prev->type && (*tokens)->prev->type <= PIPE))
			return (0);
		else if ((*tokens)->next == NULL)
		{
			return ((*tokens = (*tokens)->next), 2);
		}
		else if ((*tokens)->next && REDIRECTION <= (*tokens)->next->type && \
		(*tokens)->next->type <= HEREDOC)
		{
			*tokens = (*tokens)->next;
			return (check_is_valid_redirection(tokens));
		}
		return (check_is_valid_arg(tokens));
	}
	else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
		return (check_is_valid_redirection(&(*tokens)));
	else if (CMD <= (*tokens)->type && (*tokens)->type <= ARG)
		return (check_is_valid_arg(tokens));
	return (0);
}

/*
int	rest_check_is_valid(t_list **tokens)
{
	if (AND <= (*tokens)->type && (*tokens)->type <= PIPE)
	{
		if (AND <= (*tokens)->prev->type && (*tokens)->prev->type <= PIPE)
			return (0);
		else if ((*tokens)->next == NULL)
		{
			return ((*tokens = (*tokens)->next), 2);
		}
		else if (REDIRECTION <= (*tokens)->next->type && \
		(*tokens)->next->type <= HEREDOC)
		{
			*tokens = (*tokens)->next;
			return (check_is_valid_redirection(tokens));
		}
		return (check_is_valid_arg(tokens));
	}
	else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
		return (check_is_valid_redirection(&(*tokens)));
	else if (CMD <= (*tokens)->type && (*tokens)->type <= ARG)
		return (check_is_valid_arg(tokens));
	return (0);
}
*/

int	check_is_valid(t_list **tokens, int count_cmd_line)
{
	if (count_cmd_line == 0)
	{
		return (first_check_is_valid(tokens));
	}
	else
	{
		printf("두번째에 진입합니다.\n");
		return (rest_check_is_valid(tokens));
	}
}
