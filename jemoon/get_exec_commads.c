/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:55:03 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/09 18:46:18 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_string(t_list *tokens)
{
	int		i;
	int		string_len;
	char	*str;

	i = 0;
	string_len = strlen(tokens->token); // ft_strlen 찾아서 변경하기.
	str = (char *)malloc(sizeof(char) * (string_len + 1));
	if (str == NULL)
		return (NULL);
	strcpy(str, tokens->token); // ft_strcpy 찾아서 변경하기.
	return (str);
}

char	**set_string_array(t_list *tokens, int cmd_size)
{
	char	**string_array;
	int		i;

	i = 0;
	string_array = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (string_array == NULL)
		return (NULL);
	if (tokens->type == PIPE)
		tokens = tokens->next;
	while (i < cmd_size)
	{
		string_array[i] = set_string(tokens);
		tokens = tokens->next;
		i++;
	}
	string_array[i] = NULL;
	return (string_array);
}

void	get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i)
{
	int		cmd_size;
	char	**string_array;

	if (i == 0)
		cmd_size = get_double_string_array_size(&(*tokens));
	else
		cmd_size = get_double_string_array_size_version_2(&(*tokens));
	printf("기점의 길이를 출력합니다 : %d\n", cmd_size);
	printf("기점의 포인트를 출력합니다 : %s\n", (*tokens)->token);
	if (cmd_size == 0)
		return ;
	string_array = set_string_array(*tokens, cmd_size);
	exec_make_node(&(*exec_commads), string_array);
}
