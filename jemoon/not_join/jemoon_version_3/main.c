/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 10:23:52 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_words(char const *str)
{
	t_list	*words;
	int		index;

	index = 0;
	words = NULL;
	while (str[index] != '\0')
	{
		if (str[index] == '|')
			index = pipe_div(&words, str, index);
		else if (str[index] == '<')
			index = in_redirec_div(&words, str, index);
		else if (str[index] == '>')
			index = out_redirec_div(&words, str, index);
		else if (str[index] == '&')
			index = ampersand_div(&words, str, index);
		else if (str[index] != 32)
			index = string_div(&words, str, index);
		if (index == -1)
			return (NULL);
		else if (str[index] == '\0')
			break ;
		index++;
	}
	return (words);
}

int	check_operator_v2(const char *str, int index)
{
	int	num;

	if (str[index] == '<')
	{
		num = check_in_redirection(str, index);
		if (num == 3)
			return (error_syntax("<"));
		else if (num >= 4)
			return (error_syntax("<<"));
	}
	else if (str[index] == '>')
	{
		num = check_out_redirection(str, index);
		if (num == 3)
			return (error_syntax(">"));
		else if (num >= 4)
			return (error_syntax(">>"));
	}
	return (1);
}

int	check_operator_v1(const char *str, int index)
{
	if (str[index] == '|')
	{
		if (check_vartical_bar(str, index) == 1)
			return (error_syntax("|"));
		else
			return (error_syntax("||"));
	}
	else if (str[index] == '&')
	{
		if (check_ampersand(str, index) == 1)
			return (error_syntax("&"));
		else
			return (error_syntax("&&"));
	}
	else if (str[index] == '<' || str[index] == '>')
		return (check_operator_v2(str, index));
	return (1);
}

t_list	*mn_split(t_data *meta, char **str)
{
	t_list	*words;
	int		cmd_flag;

	if (*str == NULL)
		return (NULL);
	if ((*str)[0] == '\0')
	{
		free(*str);
		*str = NULL;
		return (NULL);
	}
	cmd_flag = check_operator_v1(*str, 0);
	if (cmd_flag == -1)
		return (NULL);
	words = split_words(*str);
	if (substitution_env_var(meta, words) == 0)
		return (free_t_list(words));
	return (words);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*tokens;
	t_data		*meta;
	t_cmd_list	*exec_cmd;

	(void)argc, (void)argv;
	meta = initial_env(envp);
	while (1)
	{
		str = readline("bash : ");
		tokens = mn_split(meta, &str);
		if (tokens == NULL)
			continue ;
		trade_exec_cmd(meta, &exec_cmd, &tokens, &str);
		if (meta->exec_cmd)
		{
			//builtin(meta);
			printf_exec_commads(meta->exec_cmd);
			free_exec_linked_list(meta->exec_cmd);
			meta->exec_cmd = NULL;
		}
		add_history(str);
		free(str);
	}
}
