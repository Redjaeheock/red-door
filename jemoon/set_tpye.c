/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tpye.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:42:51 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/07 12:31:02 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_first_node_type(t_list **tokens)
{
	if (((*tokens)->token[0] == '<' && (*tokens)->token[1] == '\0'))
		(*tokens)->type = IN_REDEC;
	else if (((*tokens)->token[0] == '>' && (*tokens)->token[1] == '\0'))
		(*tokens)->type = OUT_REDEC;
	else if (((*tokens)->token[0] == '<' && (*tokens)->token[1] == '<'))
		(*tokens)->type = HEREDOC;
	else if (((*tokens)->token[0] == '>' && (*tokens)->token[1] == '>'))
		(*tokens)->type = GR_REDEC;
	else if (((*tokens)->token[0] == '|' && (*tokens)->token[1] == '\0'))
		(*tokens)->type = PIPE;
	else if (((*tokens)->token[0] != '<' || (*tokens)->token[0] != '>'))
		(*tokens)->type = CMD;
}

void	set_tpye(t_list **tokens)
{
	if ((*tokens)->prev == NULL) /* 첫 노드의 경우, prev가 연결이 안되있어, 해당 조건으로 첫 노드 구분 */
		is_first_node_type(&(*tokens));
	else if ((*tokens)->prev->token[0] == '|' && ((*tokens)->token[0] != '<' && (*tokens)->token[0] != '>' && (*tokens)->token[0] != '|'))
		(*tokens)->type = CMD;
	else if ((*tokens)->token[0] == '|')
		(*tokens)->type = PIPE;
	else if ((*tokens)->token[0] == '<' && (*tokens)->token[1] == '\0')
		(*tokens)->type = IN_REDEC;
	else if ((*tokens)->token[0] == '>' && (*tokens)->token[1] == '\0')
		(*tokens)->type = OUT_REDEC;
	else if ((*tokens)->token[0] == '<' && (*tokens)->token[1] == '<')
		(*tokens)->type = HEREDOC;
	else if ((*tokens)->token[0] == '>' && (*tokens)->token[1] == '>')
		(*tokens)->type = GR_REDEC;
	else if ((*tokens)->prev != NULL && (*tokens)->token[0] == '-')
		(*tokens)->type = OPTION;
	else
		(*tokens)->type = ARG;
}

void	tpye_init(t_list **tokens)
{
	t_list	**tmp;

	*tmp = *tokens;
	while ((*tokens) != NULL)
	{
		set_tpye(&(*tokens));
		*tokens = (*tokens)->next;
	}
	*tokens = *tmp;
}
