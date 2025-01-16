/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:58:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/16 11:58:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h> 
# include <string.h>

typedef enum tokentype
{
	NONE,
	AND,
	OR,
	PIPE,
	REDIRECTION,
	IN_REDEC,
	OUT_REDEC,
	GR_REDEC,
	HEREDOC,
	CMD,
	OPTION,
	ARG
}	t_tokentype;

typedef struct cmd_list
{
	char			*token;
	t_tokentype		type;
	struct cmd_list	*parant;
	struct cmd_list	*prev;
	struct cmd_list	*next;
}	t_list;

typedef struct start_list
{
	char				**str;
	t_tokentype			type_pipe;
	t_tokentype			type_re;
	t_tokentype			type_ao;
	struct start_list	*next;
}	t_cmd_list;

/* main.c */

/* split_word.c */
char		*extract_word(char const *str, int start_index, int index);
t_list		*split_words(char const *str);
t_list		*mn_split(char const *str);

/* prase_utils.c */
int			skip_leading_ifs(char *str);

/* quote_parser.c */
void		parsor(char const *str, int *index);

/* linked_list.c */
void		free_linked_list(t_list *list);
t_list		*create_linked_list(char *str);
void		add_back_linked_list(t_list **tokenize, t_list *new);
void		make_node(t_list **tokenize, char *str);

/* set_tpye.c */
void		is_first_node_type(t_list **tokens);
void		tpye_init(t_list **tokens);
void		set_tpye(t_list **tokens);

/* validate_bash_syntax.c */
t_cmd_list	*validate_bash_syntax(t_list **tokens);
//void		validate_bash_syntax(t_list **tokens);

/* validate_bash_syntax.c */
int			check_is_valid_redirection(t_list **tokens);
int			check_is_valid_arg(t_list **tokens);
int			first_check_is_valid(t_list **tokens);
int			rest_check_is_valid(t_list **tokens);
int			check_is_valid(t_list **tokens, int count_cmd_line);

/* linkedlist_to_matrix.c */
int			check_redirection_size(t_list **tmp, int *array_size);
int			get_double_string_array_size(t_list **tmp);
int			get_double_string_array_size_version_2(t_list **tmp);

/* exec_commads_liked_list.c */
void	free_double_string_array(char **str);
void		free_exec_linked_list(t_cmd_list *list);
//t_cmd_list	*create_exec_linked_list(char **str);
t_cmd_list	*create_exec_linked_list(char **str, \
t_tokentype plag_pipe, t_tokentype plag_redi);
void		add_back_exec_linked_list(t_cmd_list **exec_commads, \
t_cmd_list *new);
void		exec_make_node(t_cmd_list **exec_commads, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi);
//void	exec_make_node(t_cmd_list **exec_commads, char **string_array);

/* get_exec_commads.c */
char		*set_string(t_list *tokens);
char		**set_string_array(t_list *tokens, int cmd_size, \
t_tokentype *plag_pipe, t_tokentype *plag_redi);
void		get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i);

/* printf_utils.c */
void		printf_exec_commads(t_cmd_list *exec_commands);
const char	*token_type_to_str_1(t_tokentype type);
void		printf_tokens(t_list *tokens);

#endif
