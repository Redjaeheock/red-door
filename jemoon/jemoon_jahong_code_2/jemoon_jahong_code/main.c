/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/02/17 19:56:19 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "syntax/syntax.h"
#include "built_in/built_in.h"
#include <signal.h>

t_list	*split_words(char const *str, char c)
{
	t_list	*words;
	int		index;

	index = 0;
	words = NULL;
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

int check_operator_v1(const char *str, int index)
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

t_list *mn_split(t_data *meta, char **str, char **read_str, char c)
{
	t_list	*tokens;
	t_list	*tmp;
	int		cmd_flag;

	if (c == 'c')
	{
		cmd_flag = check_operator_v1(*str, 0);
		if (cmd_flag == -1)
		{
			if (read_str == NULL)
			{
				add_history(*str);
				free(*str);
				*str = NULL;
			}
			return (NULL);
		}
	}
	tokens = split_words(*str, c);
	if (tokens == NULL)
		return (NULL);
	if (substitute_tokens(meta, tokens, c) == 0)
		return (free_t_list(tokens));
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	*meta;

	signal(SIGINT, SIG_IGN);
	(void)argc, (void)argv;
	meta = initialize_meta_token(envp);
	while (1)
	{
		str = readline("bash : ");
		if (str == NULL)
			break ;
		if (str[0] == '\0')
			continue ;	
		meta->tokens = mn_split(meta, &str, NULL, 'c');
		if (meta->tokens == NULL)
			continue ;
		printf("JEMOON_PROJECT\n");
		if (trade_exec_cmd(meta, &meta->exec_cmd, &meta->tokens, &str) < 0)
			break ;
		if (meta->exec_cmd)
		{
			builtin(meta);
			printf_exec_commads(meta->exec_cmd);
			free_exec_linked_list(meta->exec_cmd);
			meta->exec_cmd = NULL;
		}
		meta->tokens = free_t_list(meta->tokens);
		add_history(str);
		free(str);
		//printf("\n");
	}
	free_meta_token(meta);
	return (0);
}
