/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/23 19:41:12 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_make_node_2(t_cmd_list **exec_cmd, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi)
{
	t_cmd_list	*new_node;

	new_node = create_exec_linked_list(string_array, plag_pipe, plag_redi);
	if (new_node == NULL)
		return (free_exec_linked_list(new_node));
	if (*exec_cmd == NULL)
		*exec_cmd = new_node;
	else
		add_back_exec_linked_list(exec_cmd, new_node);
}

void	fill_string_array_2(char **string_array, t_list **tokens, int cmd_size)
{
	int	i;

	i = 0;
	while (i < cmd_size)
	{
		string_array[i] = set_string(*tokens);
		if (string_array[i] == NULL)
			return ;
		*tokens = (*tokens)->next;
		i++;
	}
	string_array[i] = NULL;
}

char	**set_string_array_2(t_list **tokens, int cmd_size)
{
	char	**string_array;

	if (cmd_size == 0)
		return (NULL);
	string_array = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (string_array == NULL)
		return (NULL);
	fill_string_array_2(string_array, tokens, cmd_size);
	return (string_array);
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
		return (handle_previous_redirection(check_redi));
	}
	else
	{
		return (calculate_array_size(tokens));
	}
}

void	get_exec_cmd_2(t_list *tokens, t_cmd_list **exec_cmd)
{
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;
	int			cmd_size;
	int			check_redi;
	char		**string_array;

	check_redi = 0;
	if (tokens == NULL)
		return ;
	while (tokens)
	{
		plag_pipe = NONE;
		plag_redi = NONE;
		cmd_size = get_double_string_array_size(tokens, &check_redi, \
		&plag_pipe, &plag_redi);
		if (cmd_size == 0)
			return ;
		string_array = set_string_array_2(&tokens, cmd_size);
		if (string_array == NULL)
			return ;
		exec_make_node_2(&(*exec_cmd), string_array, \
		plag_pipe, plag_redi);
	}
}
