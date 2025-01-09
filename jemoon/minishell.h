/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:58:11 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/09 15:18:10 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf함수를 사용하기위한 헤더 */
# include <stdlib.h> 
# include <string.h>

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
	char				**str;
	t_tokentype			type_pipe;
	t_tokentype			type_re;
	struct start_list 	*next;
}					t_cmd_list;

/* main.c */

/* split_word.c */
char	*extract_word(char const *str, int start_index, int index);
t_list	*split_words(char const *str);
t_list	*mn_split(char const *str);

/* prase_utils.c */
int		skip_leading_ifs(char *str);

/* quote_parser.c */
void	parsor(char const *str, int *start_index, int *index);

/* linked_list.c */
void	free_linked_list(t_list *list);
t_list	*create_linked_list(char *str);
void	add_back_linked_list(t_list **tokenize, t_list *new);
void	make_node(t_list **tokenize, char *str);

/* set_tpye.c */
void	is_first_node_type(t_list **tokens);
void	tpye_init(t_list **tokens);
void	set_tpye(t_list **tokens);

/* validate_bash_syntax.c */
int		check_is_valid_redirection(t_list **tokens);
int		check_is_valid_arg(t_list **tokens);
int		check_is_valid(t_list **tokens, int count_cmd_line);
void	validate_bash_syntax(t_list **tokens);

/* linkedlist_to_matrix.c */
int		check_redirection_size(t_list **tmp, int *array_size);
int		get_double_string_array_size(t_list **tmp);
int		get_double_string_array_size_version_2(t_list **tmp);

/* exec_commads_liked_list.c */
void	free_exec_linked_list(t_cmd_list *list);
t_cmd_list	*create_exec_linked_list(char **str);
void	add_back_exec_linked_list(t_cmd_list **exec_commads, t_cmd_list *new);
void	exec_make_node(t_cmd_list **exec_commads, char **string_array);

/* get_exec_commads.c */
char	*set_string(t_list *tokens);
char	**set_string_array(t_list *tokens, int cmd_size);
void	get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i);

#endif
