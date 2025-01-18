/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/01/18 21:25:02 by jahong           ###   ########.fr       */
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
void	*free_t_path(t_path *lsit);
void	*free_t_list(t_list *list);
void	*free_t_data(t_data *meta);
void	*free_env_resource(t_data *meta);

/*libft*/
int		ft_strlen(const char *str);
int		conditinal_strlen(const char *s, unsigned char condition);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspecial_chr(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		sndry_arr_len(void **array);
void	*free_sndry_arr(void **array);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

/*error_process*/
int		error_syntax(char *str);
void	error_qoute(int qoute);
void	*t_path_key_val_alloc_err(t_path *tmp);
void	*t_list_alloc_err(t_list *tmp);
void	*sndry_alloc_err(void **arr);
void	*t_data_alloc_err(t_data *meta);

/* token_character_check.c */
int     check_valid_wildcard(char *str, int idx, int quote);
int		check_valid_back(char *str, int idx);
int		check_quote_pair(char c, int quote);
int		check_token_chr(char *token, int idx);

/*operator_character_check.c*/
int		check_out_redirection(const char *str, int index);
int		check_in_redirection(const char *str, int index);
int		check_ampersand(const char *str, int index);
int		check_vartical_bar(const char *str, int index);
int		check_operator_set(char const *str, int index);

/*extradt_words.c*/
char	*extract_word(char const *str, int start_index, int end);
char	*extract_from_envp(char *envp, int *idx, char condition);
int		extract_key_value(t_path *tmp, char *envp, int idx);
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
int		measure_length_quote_set(char *str, int cnt);

/* substitution_token.c*/
int		count_dollar_sign(char *str);
int		mapping_dollar_sign(t_data *meta, t_list *tokens);
int		check_quote_valid(char *token);
int		substitution_env_var(t_data *meata, t_list *tokens);

/*split_criteria_dollar_sign.c*/
char	*search_n_change_dollar_sign(t_data *meta, t_list *tokens, char *str);

/*copy_n_div_token.c*/
char	**div_copy_token(char *str, int len, int quote);

/* change_dollar_sign.c */
char    *copy_split_token(char *str, int idx, int end);
char	*copy_current_process_pid(void);
char	*copy_env_value(char *str);
char	*change_null_string(void);

/* utils.c*/
char	*wild_card_substitution(void);
char	*get_exit_no(void);
char	*join_div_tokens(char **tmp, int quote, int flag);

#endif
