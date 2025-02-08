/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 18:57:39 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

char	*set_string_2(char *tokens, int cmd_size)
{
	int		string_len;
	char	*str;

	string_len = ft_strlen(tokens);
	str = (char *)malloc(sizeof(char) * (string_len + 1));
	if (str == NULL)
		return (NULL);
	strcpy(str, tokens);
	return (str);
}

void	fill_string_array_2(char **string_array, t_list **tokens, int cmd_size)
{
	int	i;
	int	f_list_len;
	int	j;

	i = 0;
	while (i < cmd_size)
	{
		if ((*tokens)->f_list != NULL)
		{
			f_list_len = sndry_arr_len((void **)(*tokens)->f_list);
			j = 0;
			while (j < f_list_len)
			{
				string_array[i] = set_string_2((*tokens)->f_list[j], cmd_size);
				if (string_array[i] == NULL)
					return ;
				i++;
				j++;
			}
		}
		else if ((*tokens)->token == NULL && cmd_size == 1)
		{
			string_array[i] = set_string_2((*tokens)->key, cmd_size);
			if (string_array[i] == NULL)
				return ;
			i++;
		}
		else if ((*tokens)->token != NULL)
		{
			string_array[i] = set_string_2((*tokens)->token, cmd_size);
			if (string_array[i] == NULL)
				return ;
			i++;
		}
		*tokens = (*tokens)->next;
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

char	*get_key_string(t_list *tokens)
{
	int		malloc_len;
	char	*return_key;

	malloc_len = ft_strlen(tokens->key);
	if (malloc_len == 0)
		return (NULL);
	return_key = (char *)malloc(sizeof(char) * (malloc_len + 1));
	if (return_key == NULL)
		return (NULL);
	strcpy(return_key, tokens->key);
	return (return_key);
}

char	*get_key(t_list *tokens, int check_redi)
{
	if (check_redi == 1 && tokens)
		return (get_key_string(tokens));
	else
		return (NULL);
}

void	get_exec_cmd_2(t_list *tokens, t_cmd_list **exec_cmd)
{
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;
	int			cmd_size;
	int			check_redi;
	char		**string_array;
	char		*key;

	check_redi = 0;
	while (tokens)
	{
		plag_pipe = NONE;
		plag_redi = NONE;
		key = get_key(tokens, check_redi);
		cmd_size = get_double_string_array_size(tokens, &check_redi, \
		&plag_pipe, &plag_redi);
		if (cmd_size == 0)
		{
			tokens = tokens->next;
			continue ;
		}
		string_array = set_string_array_2(&tokens, cmd_size);
		if (string_array == NULL)
			return ;
		exec_make_node_2(&(*exec_cmd), string_array, \
		plag_pipe, plag_redi);
		if (key != NULL)
			exec_add_key_str(&(*exec_cmd), key);
	}
}
