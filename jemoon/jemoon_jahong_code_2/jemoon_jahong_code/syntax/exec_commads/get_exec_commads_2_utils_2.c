/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:01:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/19 15:45:33 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

void	get_commads_f_list(char **string_array, t_list **tokens, \
		int *i, int cmd_size)
{
	int	j;
	int	f_list_len;

	f_list_len = sndry_arr_len((void **)(*tokens)->f_list);
	j = 0;
	while (j < f_list_len)
	{
		string_array[*i] = set_string_2((*tokens)->f_list[j], cmd_size);
		if (string_array[*i] == NULL)
			return ;
		(*i)++;
		j++;
	}
}

void	get_commads_token(char **string_array, t_list **tokens, \
		int *i, int cmd_size)
{
	string_array[*i] = set_string_2((*tokens)->token, cmd_size);
	if (string_array[*i] == NULL)
		return ;
	(*i)++;
}

void	get_commads_key(char **string_array, t_list **tokens, \
		int *i, int cmd_size)
{
	string_array[*i] = set_string_2((*tokens)->key, cmd_size);
	if (string_array[*i] == NULL)
		return ;
	(*i)++;
}

void	get_commads_key_to_token(char **string_array, t_list **tokens, \
		int *i, int redifine_size)
{
	char	**str;
	int		str_size;
	int		j;

	j = 0;
	str = ft_split((*tokens)->token, 32);
	str_size = sndry_arr_len((void **)str);
	while (j < str_size)
	{
		string_array[*i] = set_string_2(str[j], redifine_size);
		(*i)++;
		j++;
	}
	free_sndry_arr((void **)str);
}
