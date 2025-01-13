/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/13 15:31:36 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*validate_bash_syntax(t_list **tokens)
{
	int				count_cmd_line;
	t_cmd_list		*exec_commands;
	t_list			*tmp;

	tmp = *tokens;
	count_cmd_line = 0;
	exec_commands = NULL;
	while (*tokens != NULL)
	{
		printf("기점을 출력합니다 : %s \n", (*tokens)->token);
		get_exec_commads(tokens, &exec_commands, count_cmd_line);
		if (check_is_valid(tokens, count_cmd_line) == 0)
		{
			printf_exec_commads(exec_commands);
			free_exec_linked_list(exec_commands);
			*tokens = tmp;
			return (NULL);
		}
		// 실패 했을 떄, 마지막이 && 나.|| 기준으로, 다시 할당할지 끝낼 지 정하기
		// 노드의 끝이 NULL일 떄, 리턴을 때리고, 아닐 떄는 계속해서 명령어를 받아서 할당하기.
		// 유효하지 않을 때는 명령어가 syntax에서 뱉음.
		// 유효할 때는, 실행부로 던지고 다음에오는 기점을 가져다가 검사.
		// <조건문에 따라 실행이 아예 안될 떄는 syntax에서 걸러내기>
		count_cmd_line++;
	}
	printf_exec_commads(exec_commands);
	*tokens = tmp;
	return (exec_commands);
}
