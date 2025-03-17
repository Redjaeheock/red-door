/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:33:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/05 16:32:12 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

char	*handle_error(t_cmd_list **exec_cmd, char *str)
{
	free_exec_linked_list(*exec_cmd);
	*exec_cmd = NULL;
	return (str);
}

int	check_last_tokens(t_cmd_list *exec_cmd)
{
	int			i;
	t_cmd_list	*temp;

	i = 0;
	temp = exec_cmd;
	while (exec_cmd->next != NULL)
		exec_cmd = exec_cmd->next;
	if (AND <= exec_cmd->type_pipe && exec_cmd->type_pipe <= PIPE)
		i = 1;
	exec_cmd = temp;
	return (i);
}

void	combine_strings(char *return_str, char *str, char *add_str)
{
	int	i;
	int	j;
	int	str_len;
	int	add_str_len;

	i = 0;
	j = 0;
	str_len = ft_strlen(str);
	add_str_len = ft_strlen(add_str);
	while (i < str_len + add_str_len + 1)
	{
		if (i < str_len)
			return_str[i] = str[i];
		else if (i == str_len)
			return_str[i] = 32;
		else if (j < add_str_len)
		{
			return_str[i] = add_str[j];
			j++;
		}
		i++;
	}
	return_str[i] = '\0';
}

char	*make_str(char *str, char *add_str)
{
	int		str_len;
	int		add_str_len;
	char	*return_str;

	str_len = ft_strlen(str);
	add_str_len = ft_strlen(add_str);
	return_str = (char *)malloc(sizeof(char) * (str_len + add_str_len + 2));
	if (return_str == NULL)
		return (str);
	combine_strings(return_str, str, add_str);
	free(str);
	free(add_str);
	return (return_str);
}

char	*add_readline(t_cmd_list **exec_cmd, t_data *meta, char *str)
{
	char		*add_str;
	t_list		*add_tokens;
	t_cmd_list	*add_exec_cmd;

	add_tokens = NULL;
	while (check_last_tokens(*exec_cmd) == 1)
	{
		add_str = readline("> ");
		if (add_str == NULL)
		{
			free(str);
			return (NULL);
		}
		add_tokens = mn_split(meta, &add_str, 'c');
		if (add_tokens == NULL)
			continue;
		str = make_str(str, add_str);
		if (add_tokens == NULL)
			return (handle_error(exec_cmd, str));
		tpye_init(&add_tokens);
		validate_bash_syntax(&add_exec_cmd, &add_tokens);
		free_linked_list(add_tokens);
		if (add_exec_cmd == NULL)
			return (handle_error(exec_cmd, str));
		add_back_exec_linked_list(exec_cmd, add_exec_cmd);
	}
	return (str);
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	validate_operato_ending(char *str)
{
	int	str_len;

	str_len = strlen(str);
	str_len--;
	while (str[str_len] == 32)
		str_len--;
	if (str[str_len] == '|')
		return (1);
	return (0);
}

char	*make_str(char *str, char *add_str)
{
	int		i;
	int		j;
	int		str_len;
	int		add_str_len;
	char	*return_str;

	i = 0;
	j = 0;
	str_len = strlen(str);
	add_str_len = strlen(add_str);
	return_str = (char *)malloc(sizeof(char) * (str_len + add_str_len + 2));
	if (return_str == NULL)
		return (str);
	while (i < str_len + add_str_len + 1)
	{
		if (i < str_len)
			return_str[i] = str[i];
		else if (i == str_len)
			return_str[i] = 32;
		else if (j < add_str_len)
		{
			return_str[i] = add_str[j];
			j++;
		}
		i++;
	}
	return_str[i] = '\0';
	free(str);
	free(add_str);
	return (return_str);
}

int	main()
{
	char	*str;
	char	*add_str;

	while (1)
	{
		str = readline("bash :");
		while (validate_operato_ending(str) == 1)
		{
			add_str = readline("> ");
			if (str[0] == '\0')
				continue ;
			str = make_str(str, add_str);
		}
		printf("%s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
*/
