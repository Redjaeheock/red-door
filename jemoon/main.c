/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:40:49 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/12 11:22:58 by jemoon           ###   ########.fr       */
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
		if (exec_commands == NULL)
			printf("\033[31mBash syntax is invalid.\033[0m\n");
		else
		{
			printf("\033[34mBash syntax is valid.\033[0m\n");
			free_exec_linked_list(exec_commands);
		}
		free_linked_list(tokens);
		add_history(str);
		free(str);
	}
}
