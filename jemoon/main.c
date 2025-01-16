/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:40:49 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/15 20:52:58 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_char(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == 32 || str[i] == 9 || str[i] == 10)
			str[i] = 20;
		i++;
	}
}

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
		if (exec_commands != NULL)
			free_exec_linked_list(exec_commands);
		free_linked_list(tokens);
		add_history(str);
		free(str);
	}
}

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
