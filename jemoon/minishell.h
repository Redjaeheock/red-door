/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:58:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/07 11:30:47 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf함수를 사용하기위한 헤더 */
# include <stdlib.h> 

typedef	enum
{
	NONE,
	PIPE,
	REDIRECTION,
	IN_REDEC,
	OUT_REDEC,
	GR_REDEC,
	HEREDOC,
	END,
	CMD,
	OPTION,
	ARG
}	t_tokentype;

typedef struct	cmd_list
{
	char			*token;
	t_tokentype		type;
	struct cmd_list	*parant;
	struct cmd_list	*prev;
	struct cmd_list	*next;
}					t_list;

typedef struct	start_list
{
	char			**str;
	t_tokentype		tpye;
}					t_cmd_list;

/* main.c */

/* split_word.c */
char	*extract_word(char const *str, int start_index, int index);
t_list 	*split_words(char const *str);
t_list	*mn_split(char const *str);

/* prase_utils.c */
int		skip_leading_ifs(char *str);

/* quote_parser.c */
void	quote_parser(char const *str, int *index, t_list **words);
int		check_quote(char const *str, int start_index, int index);
char	*check_quote_line(char const *str, int start_index, int *index);

/* linked_list.c */
t_list	*create_linked_list(char *str);
void	add_back_linked_list(t_list **tokenize, t_list *new);
void	make_node(t_list **tokenize, char *str);
void	free_linked_list(t_list *list);

/* set_tpye.c */
void	tpye_init(t_list **tokens);
void	set_tpye(t_list **tokens);

/* validate_bash_syntax.c */
int		check_is_valid(t_list **tokens, int count_cmd_line);
void	validate_bash_syntax(t_list **tokens);


void	parsor(char const *str, int *start_index, int *index);

#endif
