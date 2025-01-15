/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/01/15 12:01:46 by jahong           ###   ########.fr       */
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
    struct cmd_list     *prev;
    struct cmd_list     *next;
    t_tokentype		    type;
    char                **path;
    char		    	*token;
}					    t_list;

typedef struct	path_list
{
    struct path_list	*next;
	char				*key;
	char				*value;
    char                *set;
}						t_path;

typedef struct meta_data
{
    struct cmd_list     *tokens;
	struct cmd_list		*cmd;
	struct path_list	*exp;
	struct path_list	*env;
	char				**envm;
    char                **args;
    char                **path;
}                      t_data;

/* free_list.c*/
void	*free_key_value(t_path *path);
void    *free_t_path(t_path *lsit);
void    *free_t_list(t_list *list);
void	*free_t_data(t_data *meta);
void	*free_env_resource(t_data *meta);

/*libft*/
int     ft_strlen(const char *str);
int     conditinal_strlen(const char *s, unsigned char condition);
int     ft_strncmp(char *s1, const char *s2, unsigned int n);
char	*ft_strdup(const char *s);
int     sndry_arr_len(void **array);
void	*free_sndry_arr(void **array);
char	**ft_split(char const *s, char c);

/*error_process*/
int     error_syntax(char *str);
void	error_qoute(int qoute);
void	*t_path_key_val_alloc_err(t_path *tmp);
void	*t_list_alloc_err(t_list *tmp);
void	*sndry_alloc_err(void **arr);
void	*t_data_alloc_err(t_data *meta);

/* quote_character_check.c */
int     check_quote_pair(char c, int quote);

/*special_character_check.c*/
int		check_out_redirection(const char *str, int index);
int		check_in_redirection(const char *str, int index);
int		check_ampersand(const char *str, int index);
int     check_vartical_bar(const char *str, int index);
int		check_operator_set(char const *str, int index);

/*extradt_words.c*/
char	*extract_word(char const *str, int start_index, int end);
char	*extract_from_envp(char *envp, int *idx, char condition);
int     extract_key_value(t_path *tmp, char *envp, int idx);
char	**extract_path(char **envp, t_path *path);

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

/* set_environ.c*/
t_data  *initial_env(char **envp);

/* check_token_quote.c*/
char	*extract_partial_token(char *str, int idx, int *end, int *quote);
char	*temporary_div_token(char *str, int *idx, int *quote);
char	**temporary_copy_token(char *str, int len);
int	    measure_length_quote_set(char *str, int cnt);

/* substitution_token.c*/
int     mapping_dollor_sign(t_list *tokens);
int     check_quote_invalid(char *token);
int     substitution_env_var(t_list *tokens);

#endif
