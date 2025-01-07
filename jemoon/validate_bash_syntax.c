/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/07 12:41:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_valid_redirection(t_list **tokens)
{
	if ((*tokens)->next == NULL)
		return (0);
	else if ((*tokens)->next->type != ARG)
		return (0);
	else
	{
		*tokens = (*tokens)->next;
		if ((*tokens)->next == NULL)
			return (1);
		*tokens = (*tokens)->next;
		return (1);
	}
}

int	chekc_is_valid_arg(t_list **tokens)
{
	*tokens = (*tokens)->next;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == PIPE)
			return (1);
		else if ((*tokens)->type == REDIRECTION)
			return (1);
		else
			*tokens = (*tokens)->next;
	}
	return (1);
}

int	check_is_valid(t_list **tokens, int count_cmd_line)
{
	if (count_cmd_line == 0)
	{
		if ((*tokens)->type == PIPE)
			return (0);
		else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
			return (check_is_valid_redirection(&(*tokens)));
		else if (CMD <= (*tokens)->type && (*tokens)->type <= ARG)
			return (chekc_is_valid_arg(&(*tokens)));
		else
			return (0);
	}
	else
	{
		if ((*tokens)->type == PIPE)
		{
			if ((*tokens)->next == NULL || (*tokens)->next->type == PIPE)
				return (0);
			return (chekc_is_valid_arg(&(*tokens)));
		}
		else if (REDIRECTION <= (*tokens)->type && (*tokens)->type <= HEREDOC)
			return (check_is_valid_redirection(&(*tokens)));
		else if (CMD <= (*tokens)->type && (*tokens)->type <= ARG)
			return (chekc_is_valid_arg(&(*tokens)));
		else
			return (0);
	}
}

void	validate_bash_syntax(t_list **tokens)
{
	int		count_cmd_line;

	count_cmd_line = 0;
	while ((*tokens) != NULL)
	{
		printf("기점을 출력합니다 : %s \n", (*tokens)->token);
		if (check_is_valid(&(*tokens), count_cmd_line) == 0)
		{
			printf("틀렸습니다.\n");
			return ;
		}
		count_cmd_line++;
	}
	printf("맞았습니다.\n");
	return ;
}

//	bool 형으로, 유효값 검사. 해당 부분이 유효하지 않을 때 False
// 	Ture 조건
//	1. 리다이렉션 뒤에, 파이프나 리다이렉션 외의 arg 올 것.
//	2. 리다이렉션 뒤 arg가 올때 까지 끊어서 검사할 것
//	3. 2번의 과정이 끝나면, 토큰의 해더값이 결국 cmd에 해당하는 곳임.
//		해당 부분이 리다이렉션인지 아닌지 구분해서 리다이렉션이면 1번과 2번 반복 아닐 시,
//		파이프 만날 때 까지 arg인지만 체크
//	4. 헤더가 파이프일 경우,  

