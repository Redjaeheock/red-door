/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:40:49 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/18 15:45:23 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*tokens;
	t_cmd_list	*exec_commands;

	(void)argc, (void)argv, (void)envp;
	tokens = NULL;
	while (1)
	{
		str = readline("bash : ");
		if (str[0] == '\0')
			continue ;
		tokens = mn_split(str + skip_leading_ifs(str));
		tpye_init(&tokens);
		printf_tokens(tokens);
		exec_commands = validate_bash_syntax(&tokens);
		free_linked_list(tokens);
		if (exec_commands != NULL)
		{
			str = add_readline(&exec_commands, str);
			free_exec_linked_list(exec_commands);
		}
		add_history(str);
		free(str);
	}
}

/*
int	check_last_tokens(t_cmd_list *exec_commads)
{
	int			i;
	t_cmd_list	*temp;

	i = 0;
	temp = exec_commads;
	while (exec_commads->next != NULL)
		exec_commads = exec_commads->next;
	if (AND <= exec_commads->type_pipe && exec_commads->type_pipe <= PIPE)
		i = 1;
	exec_commads = temp;
	return (i);
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

char	*add_readline(t_cmd_list **exec_commads, char *str)
{
	char		*add_str;
	t_list		*add_tokens;
	t_cmd_list	*add_exec_commads;

	add_tokens = NULL;
	while (check_last_tokens(*exec_commads) == 1)
	{
		add_str = readline("> ");
		if (add_str[0] == '\0')
			continue ;
		add_tokens = mn_split(str + skip_leading_ifs(add_str));
		tpye_init(&add_tokens);
		printf_tokens(add_tokens);
		add_exec_commads = validate_bash_syntax(&add_tokens);
		str = make_str(str, add_str);
		if (add_exec_commads == NULL)
			return (str);
		add_back_exec_linked_list(exec_commads, add_exec_commads);
	}
	return (str);
}
*/

/*
int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*tokens;

	tokens = NULL;
	while (1)
	{
		str = readline("bash : ");
		if (str[0] == '\0')
			continue ;
		tokens = mn_split(str + skip_leading_ifs(str));
		tpye_init(&tokens);
		printf_tokens(tokens);
		validate_bash_syntax(&tokens);
		free_linked_list(tokens);
		add_history(str);
		free(str);
	}
}
*/
