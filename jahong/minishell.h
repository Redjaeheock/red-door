/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/01/24 21:10:49 by jahong           ###   ########.fr       */
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

typedef struct	temp_list
{
	struct temp_list	*next;
	char				*key;
	char				*value;
}						t_tmp;

typedef struct  cmd_list
{
	struct cmd_list     *prev;
	struct cmd_list     *next;
	t_tokentype		    type;
	char				*key;
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
	struct path_list	*exp;
	struct path_list	*env;
	char				**envm;
	char                **path;
	char                *exit_n;
	char                *pid_n;
	char                *lval;
}                      t_data;

/* free_list.c*/
void	*free_key_value(t_path *path);
void	*free_t_path(t_path *lsit);
void	*free_t_list(t_list *list);
void	*free_t_data(t_data *meta);
void	*free_meta_token(t_data *meta);

/* free_tmp_list.c */
void	free_single_tmp_node(t_tmp *node);
void	*free_tmp_list(t_tmp *node);

/*error_process*/
int		error_syntax(char *str);
void	error_qoute(int qoute);
void	*memory_alloc_error(void);
void	*t_path_key_val_alloc_err(t_path *tmp);
void	*t_list_alloc_err(t_list *tmp);
void	*sndry_alloc_err(void **arr);
void	*t_data_alloc_err(t_data *meta);
void	*t_tmp_alloc_err(t_tmp *node);

/* initialize_meta_token.c*/
t_data  *initialize_meta_token(char **envp);

/* linked_list.c */
t_list	*create_linked_list(char *str);
void	add_back_linked_list(t_list *tokenize, t_list *new);
void	make_node(t_list **tokenize, char *str);

/* linked_tmp_list */
t_tmp	*last_tmp_list(t_tmp *node);
t_tmp	*create_new_tmp_list(char *str1, char *str2);
t_tmp	*make_tmp_node(t_tmp *node, char *str1, char *str2);

/*libft*/
int		ft_strlen(const char *str);
int		conditinal_strlen(const char *s, unsigned char condition);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		sndry_arr_len(void **array);
void	*free_sndry_arr(void **array);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strjoin_v2(const char *s1, const char *s2);

/* main.c */
int		check_operator_v1(const char *str, int index);

/* extradt_words.c */
char	*extract_word(char const *str, int start_index, int end);
char	*extract_from_envp(char *envp, int *idx, char condition);
int		extract_key_value(t_path *tmp, char *envp, int idx);
char	**extract_path(t_path *path);

/* split_words.c */
int		string_div(t_list **words, char const *str, int index);
int		ampersand_div(t_list **words, const char *str, int index, char c);
int		in_redirec_div(t_list **words, const char *str, int index, char c);
int		out_redirec_div(t_list **words, const char *str, int index, char c);
int		pipe_div(t_list **words, const char *str, int index, char c);

/* token_character_check.c */
int		search_wildcard_into_token(char *str);
int     check_valid_wildcard(char *str, int idx, int quote);
int		check_valid_back(char *str, int idx);
int		check_quote_pair(char c, int quote);

/* operator_character_check.c */
int		check_out_redirection(const char *str, int index);
int		check_in_redirection(const char *str, int index);
int		check_ampersand(const char *str, int index);
int		check_vartical_bar(const char *str, int index);
int		check_operator_set(char const *str, int index);

/* devideing_sub_token.c*/
char	*extract_partial_token(char *str, int idx, int *end, int *quote);
char	*temporary_div_token(char *str, int *idx, int *quote);
char	**dividing_sub_token(char *str, int len);


/* deviding_copied_token.c */
t_tmp	*dividing_copied_token(char *str);

/* substitute_token.c*/
int		subtitute_dollar_sign_n_wlidcard(t_data *meta, t_list *tokens);
int		check_quote_valid(char *token);
int		substitute_tokens(t_data *meata, t_list *tokens, char c);

/* substitute_dollar_sign.c */
t_tmp	*substitute_dollar_sign(t_data *meta, char **str);

/* substitute_wildcard.c */
int		substitute_wildcard(t_data *meta, t_list *tokens);

/* change_dollar_sign.c */
char	*copy_current_process_pid(void);
char	*change_null_string(void);

/* join_sub_tokens*/
int		join_sub_tokens(t_list *tokens, t_tmp *node);
// char	*join_splited_sub_token(t_tmp *tmp);

/* utils.c*/
char	search_chr_in_str(char *str, char c);
char	are_all_characters_same(char *str, char c);
char	*get_exit_no(void);

/*utils2.c*/
char    *copy_index_range(char *str, int idx, int end);
int		ck_part_of_special_chr(int c);

#endif
