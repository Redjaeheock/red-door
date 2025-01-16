/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/15 21:02:21 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			printf("\033[31msyntax error\033[0m\n");
			free_exec_linked_list(exec_commands);
			*tokens = tmp;
			return (NULL);
		}
		count_cmd_line++;
	}
	printf_exec_commads(exec_commands);
	printf("\033[34mBash syntax is valid.\033[0m\n");
	*tokens = tmp;
	return (exec_commands);
}

/*
void	validate_bash_syntax(t_list **tokens)
{
	int				count_cmd_line;
	t_list			*tmp;
	t_cmd_list		*exec_commands;

	tmp = *tokens;
	count_cmd_line = 0;
	exec_commands = NULL;
	while (*tokens != NULL)
	{
		printf("기점을 출력합니다 : %s \n", (*tokens)->token);
		get_exec_commads(tokens, &exec_commands, count_cmd_line);
		if (check_is_valid(tokens, count_cmd_line) == 0)
		{
			//printf_exec_commads(exec_commands);
			//free_exec_linked_list(exec_commands);
			*tokens = tmp;
			printf("\033[31m유요하지 않는 값입니다.\033[0m\n");
			return ;
		}
		// 실패 했을 떄, 마지막이 && 나.|| 기준으로, 다시 할당할지 끝낼 지 정하기
		// 노드의 끝이 NULL일 떄, 리턴을 때리고, 아닐 떄는 계속해서 명령어를 받아서 할당하기.
		// 유효하지 않을 때는 명령어가 하나라도 있을 떄syntax에서 뱉음.
		// | 파이프처럼 && || 신텍스 기준이 비슷해 보임.
		// 유효한지만 검사하니까, 굳이 유효했다고 던지는게 아니라, 전체 연결리스트에 우선 담아두기.
		// <조건문에 따라 실행이 아예 안될 떄는 syntax에서 걸러내기>
		count_cmd_line++;
	}
	//printf_exec_commads(exec_commands);
	*tokens = tmp;
	printf("\033[34m유요한 값입니다.\033[0m\n");
	return ;
}
*/
