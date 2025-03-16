/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/03/16 11:43:19 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax/syntax.h"
#include "built_in/built_in.h"
#include <signal.h>

int	g_ws = 0;

t_list	*split_words(char const *str, char c)
{
	t_list	*words;
	int		index;

	words = NULL;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '|')
			index = pipe_div(&words, str, index, c);
		else if (str[index] == '<')
			index = in_redirec_div(&words, str, index, c);
		else if (str[index] == '>')
			index = out_redirec_div(&words, str, index, c);
		else if (str[index] == '&')
			index = ampersand_div(&words, str, index, c);
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

int	mn_split(t_data *meta, char **str, char c)
{
	t_list	*tokens;
	int		cmd_flag;

	if (*str == NULL)
		return (-1);
	if ((*str)[0] == '\0')
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	if (c == 'c')
	{
		cmd_flag = check_operator_v1(*str, 0);
		if (cmd_flag == -1)
			return (-1);
	}
	tokens = split_words(*str, c);
	if (tokens == NULL)
		return ((free(*str), -1));
	if (substitute_tokens(meta, tokens, c) == 0)
		return (/*(add_history(*str), free(*str),*/ free_t_list(tokens), 0);
	if (meta->tokens == NULL)
		meta->tokens = tokens;
	else
		add_back_linked_list(meta->tokens, tokens);
	return (1);
}

void	add_history_and_free(char **str)
{
	if (*str == NULL)
		return ;
	add_history(*str);
	free(*str);
	*str = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	*meta;
	int		i;

	(void)argc, (void)argv;
	meta = initialize_meta_token(envp);
	while (meta != NULL)
	{
		str = readline("bash: ");
		if (str == NULL)
			break ;
		i = mn_split(meta, &str, 'c');
		if (i < 1)
		{
			add_history_and_free(&str);
			continue ;
		}
		if (trade_exec_cmd(meta, &meta->exec_cmd, &meta->tokens, &str) < 0)
			break ;
		run(meta);
		rutin_free(meta, str);
	}
	free_meta_token(meta);
	return (0);
}
