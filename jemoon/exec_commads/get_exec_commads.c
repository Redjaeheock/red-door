/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:55:03 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/18 15:18:39 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	recycle_size(t_list *tokens, int *cmd_size, \
t_tokentype *plag_pipe, t_tokentype *plag_redi)
{
	int	size;
	int	i;

	i = 0;
	size = *cmd_size;
	if (AND <= tokens->type && tokens->type <= PIPE)
		tokens = tokens->next;
	if (tokens == NULL && *cmd_size == 1)
		return ;
	while (i < size)
	{
		if ((AND <= tokens->type && tokens->type <= PIPE) && \
		!(AND <= tokens->prev->type && tokens->prev->type <= PIPE))
		{
			(*cmd_size)--;
			(*plag_pipe) = tokens->type;
		}
		else if (REDIRECTION <= tokens->type && tokens->type <= HEREDOC)
		{
			(*cmd_size)--;
			(*plag_redi) = tokens->type;
		}
		i++;
		tokens = tokens->next;
	}
}

char	*set_string(t_list *tokens)
{
	int		string_len;
	char	*str;

	string_len = strlen(tokens->token);
	str = (char *)malloc(sizeof(char) * (string_len + 1));
	if (str == NULL)
		return (NULL);
	strcpy(str, tokens->token);
	return (str);
}

void	fill_string_array(char **string_array, t_list *tokens, int cmd_size)
{
	int	i;

	i = 0;
	while (i < cmd_size)
	{
		if ((AND <= tokens->type && tokens->type <= PIPE) && \
		tokens->prev == NULL)
		{
			string_array[i] = set_string(tokens);
			tokens = tokens->next;
			i++;
		}
		else if (((AND <= tokens->type && tokens->type <= PIPE) && \
		!(AND <= tokens->prev->type && tokens->prev->type <= PIPE)) || \
		(REDIRECTION <= tokens->type && tokens->type <= HEREDOC))
			tokens = tokens->next;
		else
		{
			string_array[i] = set_string(tokens);
			tokens = tokens->next;
			i++;
		}
	}
	string_array[i] = NULL;
}

char	**set_string_array(t_list *tokens, int cmd_size, \
t_tokentype *plag_pipe, t_tokentype *plag_redi)
{
	char	**string_array;

	recycle_size(tokens, &cmd_size, &(*plag_pipe), &(*plag_redi));
	if (cmd_size == 0)
		return (NULL);
	string_array = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (string_array == NULL)
		return (NULL);
	if ((AND <= tokens->type && tokens->type <= PIPE) && cmd_size != 1)
		tokens = tokens->next;
	fill_string_array(string_array, tokens, cmd_size);
	return (string_array);
}

void	get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i)
{
	int			cmd_size;
	char		**string_array;
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;

	plag_pipe = NONE;
	plag_redi = NONE;
	if (i == 0)
		cmd_size = get_first_double_string_array_size(&(*tokens));
	else
		cmd_size = get_rest_double_string_array_size(&(*tokens));
	printf("기점의 길이를 출력합니다 : %d\n", cmd_size);
	printf("기점의 포인트를 출력합니다 : %s\n", (*tokens)->token);
	if (cmd_size == 0)
		return ;
	string_array = set_string_array(*tokens, cmd_size, &plag_pipe, &plag_redi);
	if (string_array == NULL)
		return ;
	printf("[%d %d]\n", plag_pipe, plag_redi);
	exec_make_node(&(*exec_commads), string_array, plag_pipe, plag_redi);
}
