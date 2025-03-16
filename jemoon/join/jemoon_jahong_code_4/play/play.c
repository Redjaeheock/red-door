/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:34:04 by jahong            #+#    #+#             */
/*   Updated: 2025/02/24 12:08:43 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../syntax/syntax.h"
#include "../built_in/built_in.h"

int	play(t_data *meta)
{
	t_cmd_list	*temp;

	temp = meta->exec_cmd;
	if (temp)
	{
		builtin(meta);
	}
	return (0);
}

int	rutin_free(t_data *meta, char *str)
{
	if (meta->exec_cmd)
	{
		printf_exec_commads(meta->exec_cmd);
		free_exec_linked_list(meta->exec_cmd);
		meta->exec_cmd = NULL;
	}
	meta->tokens = free_t_list(meta->tokens);
	add_history_and_free(&str);
	return (0);
}

char	*str_malloc(char *str)
{
	int		i;
	int		j;
	char	*malloc_str;

	j = 0;
	i = ft_strlen(str);
	malloc_str = (char *)malloc(sizeof(char) * i + 1);
	if (malloc_str == NULL)
		return (NULL);
	while (j < i)
	{
		malloc_str[j] = str[j];
		j++;
	}
	malloc_str[j] = '\0';
	return (malloc_str);
}

/*
void	get_exit_no(t_data *meta, int status)
{
	int		exit_no;
	char	*str;
	t_path	*temp;
	t_path	*add_exit_no;

	exit_no = (status >> 8) & 0xFF;
	str = ft_itoa(exit_no);
	add_exit_no = make_t_path();
	add_exit_no->key = str_malloc("?");
	add_exit_no->value = str;
	add_exit_no->set = NULL;
	process_export_entry(meta, add_exit_no, env_add, 0);
}
*/