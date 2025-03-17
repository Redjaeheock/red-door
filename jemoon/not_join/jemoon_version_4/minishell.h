/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/02/03 15:28:57 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline 함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history 함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf 함수를 사용하기위한 헤더 */
# include <stdlib.h>
# include <dirent.h>               /* opendir, readdir, closedir 함수를 사용하기 위한 헤더*/
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

typedef struct temp_list
{
	struct temp_list	*next;
	char				*key;
	char				*value;
}						t_tmp;

typedef struct cmd_list
{
	struct cmd_list		*prev;
	struct cmd_list		*next;
	t_tokentype			type;
	char				**f_list;
	char				*key;
	char				*token;
}						t_list;

typedef struct start_list
{
	struct start_list	*prev;
	struct start_list	*next;
	t_tokentype			type_pipe;
	t_tokentype			type_re;
	char				*key;
	char				**str;
}	t_cmd_list;

typedef struct path_list
{
	struct path_list	*next;
	char				*key;
	char				*value;
	char				*set;
}						t_path;

typedef struct meta_data
{
	struct cmd_list		*tokens;
	struct path_list	*exp;
	struct path_list	*env;
	struct start_list	*exec_cmd;
	char				**envm;
	char				**path;
	char				*exit_n;
	char				*pid_n;
	char				*lval;
}						t_data;

/* free_list.c*/
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
int		conditional_strlen(const char *s, unsigned char condition);
int		conditional_jump_len(const char *s, unsigned char condition);
int		quote_set_jump_len(const char *s);
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
char	*ft_str_tail_str(const char *big, const char *little);


/* main.c */
int		check_operator_v1(const char *str, int index);

/* extradt_words.c */
char	*extract_word(char const *str, int start_index, int end);
char	*extract_from_envp(char *envp, int *idx, char condition);
int		extract_key_value(t_path *tmp, char *envp);
char	**extract_path(t_path *path);

/* split_words.c */
int		string_div(t_list **words, char const *str, int index);
int		ampersand_div(t_list **words, const char *str, int index, char c);
int		in_redirec_div(t_list **words, const char *str, int index, char c);
int		out_redirec_div(t_list **words, const char *str, int index, char c);
int		pipe_div(t_list **words, const char *str, int index, char c);

/* token_character_check.c */
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
int		subtitute_dollar_sign(t_data *meta, t_list *tokens, char c);
int		check_quote_valid(char *token);
int		substitute_tokens(t_data *meata, t_list *tokens, char c);

/* substitute_dollar_sign.c */
t_tmp	*do_substitute_dollar_sign(t_data *meta, char **str, char c);

/* substitute_wildcard1.c */
int		substitute_wildcard(t_data *meta, t_list *tokens);

/* substitute_wildcard2.c */
int		change_only_wildcard_token(t_list *node);
int		change_partial_wildcard2(t_path *env, t_list *node, int	idx, int end);
int		change_partial_wildcard1(t_list *node, char *str);

/* change_dollar_sign.c */
char	*copy_current_process_pid(void);
char	*change_null_string(void);

/* join_sub_tokens*/
int		join_sub_tokens(t_list *tokens, t_tmp *node, char c);

/* utils.c*/
char	search_chr_in_str(char *str, char c);
char	are_all_characters_same(char *str, char c);
char	*get_exit_no(void);

/*utils2.c*/
char	*search_value_using_key(t_path *path, char *src);
char	*copy_conditional_index_range(char *str, int idx, int end, char c);
char    *copy_index_range(char *str, int idx, int end);
int		ck_part_of_special_chr(int c);

/* utils_directory.c */
int		count_valid_filename(char **list, char *str);
int		search_str_in_f_list(t_list *node, char **list, char *str);
char	**take_filenames1(struct dirent *entry, DIR *dir, char *path, int len);
int		open_n_filter_current_filenames(t_list *node, char *str, int len);
int		open_n_read_current_filenames(t_list *node, int len);
int		count_list_current_directory(void);

/* othoer_functions.c*/
int		is_token_all_null_after_join(t_tmp *tmp);
char	*copy_quote_set_jump(char *s, char *tmp, int len);

/*main. c*/
t_list	*mn_split(t_data *meta, char **str, char c);


void	free_linked_list(t_list *list);
#endif
