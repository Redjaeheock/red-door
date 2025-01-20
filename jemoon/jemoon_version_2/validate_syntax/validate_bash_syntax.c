/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bash_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/20 16:18:55 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_make_node_2(t_cmd_list **exec_commads, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi)
{
	t_cmd_list	*new_node;

	new_node = create_exec_linked_list(string_array, plag_pipe, plag_redi);
	if (new_node == NULL)
		return (free_exec_linked_list(new_node));
	if (*exec_commads == NULL)
		*exec_commads = new_node;
	else
		add_back_exec_linked_list(exec_commads, new_node);
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
	int	array_size;

	array_size = 0;
	if (REDIRECTION <= tokens->type && tokens->type <= HEREDOC)
	{
		(*check_redi) = 1;
		(*plag_redi) = tokens->type;
		return (1); 
	}
	else if (AND <= tokens->type && tokens->type <= PIPE)
	{
		(*plag_pipe) = tokens->type;
		return (1);
	}
	else if (*check_redi == 1)
	{
		(*check_redi) = 0;
		return (1); 
	}
	else
	{
		while (tokens && !(AND <= tokens->type && tokens->type <= HEREDOC))
		{
			array_size++;
			tokens = tokens->next;
		}
		return (array_size);
	}
	return (array_size);
}

void	get_exec_commads_2(t_list *tokens, t_cmd_list **exec_commands)
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
		exec_make_node_2(&(*exec_commands), string_array, \
		plag_pipe, plag_redi);
	}
}

void	validate_bash_syntax(t_cmd_list **exec_commands, t_list **tokens)
{
	int		count_cmd_line;
	t_list	*tmp;

	tmp = *tokens;
	count_cmd_line = 0;
	*exec_commands = NULL;
	while (*tokens != NULL)
	{
		if (check_is_valid(tokens, count_cmd_line) == 0)
		{
			error_syntax((*tokens)->token);
			*tokens = tmp;
			return ;
		}
		count_cmd_line++;
	}
	*tokens = tmp;
	get_exec_commads_2(*tokens, exec_commands);
}
