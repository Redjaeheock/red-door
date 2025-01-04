/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/01/04 19:14:45 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf함수를 사용하기위한 헤더 */
# include <stdlib.h> 

typedef enum {
    NONE,
    PIPE,
    REDIRECTION,
    CMD,
    OPTION,
    ARG
}	t_tokentype;

typedef struct  cmd_list
{
    char			*token;
    t_tokentype		type;
    struct cmd_list	*parant;
    struct cmd_list	*prev;
    struct cmd_list	*next;
}					t_list;

typedef struct	path_list
{
	char				*key;
	char				*value;
	struct path_list	*next;
}						t_path;

typedef struct meta_data
{
	struct cmd_list		*tokens;
	struct path_list	*exp;
	struct path_list	*env;
	char				**envm;
};

/*libft*/
int     ft_strlen(const char *str);
int     ft_strncmp(char *s1, const char *s2, unsigned int n);

/*error_print.c*/
int     error_syntax(char *str);

/*special_character_check.c*/
int		check_out_redirection(const char *str, int index);
int		check_in_redirection(const char *str, int index);
int		check_ampersand(const char *str, int index);
int     check_vartical_var(const char *str, int index);
int		operator_check(char const *str, int index);

/*extradt_words.c*/
char	*extract_word(char const *str, int start_index, int end);

/* split_words.c */
int		string_div(t_list **words, char const *str, int index);
int		ampersand_div(t_list **words, const char *str, int index);
int		in_redirec_div(t_list **words, const char *str, int index);
int		out_redirec_div(t_list **words, const char *str, int index);
int		pipe_div(t_list **words, const char *str, int index);

/* linked_list.c */
t_list	*create_linked_list(char *str);
void	add_back_linked_list(t_list *tokenize, t_list *new);
void	make_node(t_list **tokenize, char *str);
void	free_linked_list(t_list *list);

#endif
