/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2_utils_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:01:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/10 12:20:52 by jemoon           ###   ########.fr       */
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

	i = 0;
	while (i < cmd_size)
	{
		if ((*tokens)->f_list != NULL)
			get_commads_f_list(string_array, tokens, &i, cmd_size);
		else if ((*tokens)->token == NULL && cmd_size == 1)
			get_commads_key(string_array, tokens, &i, cmd_size);
		else if ((*tokens)->token != NULL)
			get_commads_token(string_array, tokens, &i, cmd_size);
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
