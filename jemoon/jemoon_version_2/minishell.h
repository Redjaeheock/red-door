/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 20:51:54 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf함수를 사용하기위한 헤더 */
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
	struct cmd_list		*prev;
	struct cmd_list		*next;
	t_tokentype			type;
	char				**path;
	char				*token;
}	t_list;

typedef struct start_list
{
	char				**str;
	t_tokentype			type_pipe;
	t_tokentype			type_re;
	struct start_list	*next;
}	t_cmd_list;

typedef struct path_list
{
	struct path_list	*next;
	char				*key;
	char				*value;
	char				*set;
}	t_path;

typedef struct meta_data
{
	struct cmd_list		*tokens;
	struct cmd_list		*cmd;
	struct path_list	*exp;
	struct path_list	*env;
	struct start_list	*exec_commads;
	char				**envm;
	char				**args;
	char				**path;
}	t_data;

/* free_list.c*/
void		*free_key_value(t_path *path);
void		*free_t_path(t_path *lsit);
void		*free_t_list(t_list *list);
void		*free_t_data(t_data *meta);
void		*free_env_resource(t_data *meta);

/*libft*/
int			ft_strlen(const char *str);
int			conditinal_strlen(const char *s, unsigned char condition);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isspecial_chr(int c);
int			ft_strncmp(char *s1, const char *s2, unsigned int n);
char		*ft_strdup(const char *s);
int			sndry_arr_len(void **array);
void		*free_sndry_arr(void **array);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);

/*error_process*/
int			error_syntax(char *str);
void		error_qoute(int qoute);
void		*t_path_key_val_alloc_err(t_path *tmp);
void		*t_list_alloc_err(t_list *tmp);
void		*sndry_alloc_err(void **arr);
void		*t_data_alloc_err(t_data *meta);

/* token_character_check.c */
int			check_valid_back(char *str, int idx);
int			check_quote_pair(char c, int quote);
int			check_token_chr(char *token, int idx);

/*operator_character_check.c*/
int			check_out_redirection(const char *str, int index);
int			check_in_redirection(const char *str, int index);
int			check_ampersand(const char *str, int index);
int			check_vartical_bar(const char *str, int index);
int			check_operator_set(char const *str, int index);

/*extradt_words.c*/
char		*extract_word(char const *str, int start_index, int end);
char		*extract_from_envp(char *envp, int *idx, char condition);
int			extract_key_value(t_path *tmp, char *envp, int idx);
char		**extract_path(t_path *path);

/* split_words.c */
int			string_div(t_list **words, char const *str, int index);
int			ampersand_div(t_list **words, const char *str, int index);
int			in_redirec_div(t_list **words, const char *str, int index);
int			out_redirec_div(t_list **words, const char *str, int index);
int			pipe_div(t_list **words, const char *str, int index);

/* set_environ.c*/
t_data		*initial_env(char **envp);

/* check_token_quote.c*/
char		*extract_partial_token(char *str, int idx, int *end, int *quote);
char		*temporary_div_token(char *str, int *idx, int *quote);
char		**temporary_copy_token(char *str, int len);
int			measure_length_quote_set(char *str, int cnt);

/* substitution_token.c*/
int			count_dollar_sign(char *str);
int			mapping_dollar_sign(t_data *meta, t_list *tokens);
int			check_quote_valid(char *token);
int			substitution_env_var(t_data *meata, t_list *tokens);

/*split_criteria_dollar_sign.c*/
char		*search_n_change_dollar_sign(t_data *meta, char *str);

/*copy_n_div_token.c*/
char		**div_copy_token(char *str, int len);

/* change_dollar_sign.c */
char		*copy_current_process_pid(void);
char		*copy_env_value(char *str);
char		*change_null_string(void);

/* utils.c*/
char		*get_exit_no(void);

/* jemoon code */
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
void		validate_bash_syntax(t_cmd_list **exec_commands, t_list **tokens);

/* validate_bash_syntax.c */
int			check_is_valid_redirection(t_list **tokens);
int			check_is_valid_arg(t_list **tokens);
int			first_check_is_valid(t_list **tokens);
int			rest_check_is_valid(t_list **tokens);
int			check_is_valid(t_list **tokens, int count_cmd_line);

/* linkedlist_to_matrix.c */
int			check_redirection_size(t_list **tmp, int *array_size);
int			get_first_double_string_array_size(t_list **tmp);
int			get_rest_double_string_array_size(t_list **tmp);

/* exec_commads_liked_list.c */
void		free_double_string_array(char **str);
void		free_exec_linked_list(t_cmd_list *list);
t_cmd_list	*create_exec_linked_list(char **str, \
t_tokentype plag_pipe, t_tokentype plag_redi);
void		add_back_exec_linked_list(t_cmd_list **exec_commads, \
t_cmd_list *new);
void		exec_make_node(t_cmd_list **exec_commads, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi);

/* get_exec_commads.c */
char		*set_string(t_list *tokens);
char		**set_string_array(t_list *tokens, int cmd_size, \
t_tokentype *plag_pipe, t_tokentype *plag_redi);
void		get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i);

/* printf_utils.c */
void		printf_exec_commads(t_cmd_list *exec_commands);
const char	*token_type_to_str_1(t_tokentype type);
void		printf_tokens(t_list *tokens);

/* readline_utils.c */

int			check_last_tokens(t_cmd_list *exec_commads);
char		*make_str(char *str, char *add_str);
char		*add_readline(t_cmd_list **exec_commads, t_data *meta, char *str);

t_list		*mn_split(t_data *meta, char **str);
void		trade_exce_cmd(t_data *meta, t_cmd_list **exec_commdas, \
t_list **tokens, char **str);

#endif
