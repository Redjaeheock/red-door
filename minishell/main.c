/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/03/22 16:13:38 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax/syntax.h"
#include "built_in/built_in.h"
#include <signal.h>

int	g_ws = 0;

t_list	*split_words(char const *str)
{
	t_list	*words;
	int		index;

	words = NULL;
	index = 0;
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
			return (free_t_list(words), NULL);
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

	if (*str == NULL)
		return (-1);
	if ((*str)[0] == '\0')
		return (0);
	if (check_operator_v2(*str, 0) == -1)
		return (-1);
	tokens = split_words(*str);
	if (tokens == NULL)
	{
		meta->tokens = free_t_list(meta->tokens);
		return (-1);
	}
	if (count_quote_set(tokens, c) == 0)
		return (free_t_list(tokens), 0);
	if (meta->tokens == NULL)
		meta->tokens = tokens;
	else
		add_back_linked_list(meta->tokens, tokens);
	return (1);
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
		run(meta, meta->exec_cmd);
		rutin_free(meta, str);
	}
	free_meta_token(meta);
	return (0);
}
