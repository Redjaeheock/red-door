/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2025/03/08 15:54:04 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <readline/readline.h>    /* readline 함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history 함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf 함수를 사용하기위한 헤더 */
# include <stdlib.h>
# include <dirent.h>               /* opendir, readdir, closedir 함수를 사용하기 위한 헤더*/
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

extern int g_ws;

typedef enum tokentype
{
	NONE = 0,
	CMD,
	OPTION,
	ARG,
	AND,
	OR,
	PIPE,
	REDIRECTION,
	IN_REDEC,
	OUT_REDEC,
	GR_REDEC,
	HEREDOC
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
	t_tokentype			type_cmd;
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
	char				*home;
	char				*pwd;
	char				*oldpwd;
	char				*exit_n;
	char				*pid_n;
	char				*lval;
	int					oldstdin;
	int					oldstdout;
	int					oldstderr;
	int					heredoc;
	int					stdin_flag;
	int					pids;
	unsigned int		ppid;
}						t_data;

/* free_list.c*/
void	*free_t_path(t_path *lsit);
void	*free_t_list(t_list *list);
void	*free_t_data(t_data *meta);
void	*free_meta_token(t_data *meta);

/* free_tmp_list.c */
void	free_single_tmp_node(t_tmp *node);
void	*free_tmp_list(t_tmp *node);

/* free_secondary_array.c */
void	*free_sndry_arr(void **array);
void	*free_multi_2d_arrs(void **array1, void **array2);

/* unlink_files.c */
void	unlink_files(t_list	*tokens);

/*error_process*/
int		error_syntax(char *str);
void	error_qoute(int qoute);
void	*memory_alloc_error(void);
void	*t_path_key_val_alloc_err(t_path *tmp);
void	*t_list_alloc_err(t_list *tmp);
void	*sndry_alloc_err(void **arr);
void	*t_data_alloc_err(t_data *meta);
void	*t_tmp_alloc_err(t_tmp *node);
void	wranning_msg(char *eof);

/* initialize_meta_token.c*/
t_data	*initialize_meta_token(char **envp);

/* signal_process.c */
// void	handle_heredoc(int signum, sigset_t *preset);
// void	handle_rollback(int signum, sigset_t *preset);
void	set_up_signal(t_data *meta);
void	child_process_kill(void);

/* here_doc */
int		here_doc(t_data *meta, t_list *tokens);

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
int		reverse_conditiona_strlen(const char *s, unsigned char condition);
int		conditional_jump_len(const char *s, unsigned char condition);
int		quote_set_jump_len(const char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
int		sndry_arr_len(void **array);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_strjoin_v2(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_str_head_str(const char *big, const char *little);
char	*ft_str_tail_str(const char *big, const char *little);
char	**ft_add_str_to_2d_arr(char **arr, char *str);
char	**ft_add_2d_arr_to_str(char *str, char **arr);
int		ft_strncmp(char *s1, const char *s2, unsigned int n);
void	ft_sort_2d_arr(char **str);
char	**ft_merge_2d_arr(char **arr1, char **arr2);
void	ft_putstr_fd(char *s, int fd);

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

/* substitute_dollar_sign2.c*/
int		check_split_point_str(char *str);

/* substitute_dollar_sing3.c */
t_tmp	*change_dollar_sign(t_data *meta, char *str);

/* substitute_dollar_sign_check.c */
t_tmp	*pass_substitute(char *str);
int		check_pass_substitute(char *str, char c);

/* change_dollar_sign.c */
int		check_except_substitution(t_data *meta, t_tmp *node);
char	*copy_current_process_pid(t_data *meta);
char	*change_null_string(void);

/*	change_dollar_underbar.c */
int		change_dollar_underbar(t_data *meta, t_cmd_list *exec_cmd);

/* join_sub_tokens*/
int		join_sub_tokens(t_list *tokens, t_tmp *node, char c);

/* substitute_wildcard3.c */
char	**open_multi_directory(char *path, char **f_list);
int		substitute_wildcard(t_list *tokens);

/* exclusive_use_wildcard_split.c */
char	**exclusive_use_wildcard_split1(char *src, int len, int row, int idx);
int		exclusive_use_wildcard_len(char *str);

/* exclusive_use_wildcard_join.c */
int		exclusive_use_wildcard_valid_check(char *path);
int		exclusive_use_wildcard_join_len(char **paths);
char	*exclusive_use_wildcard_join2(char **paths, int *row);
char	**exclusive_use_wildcard_join1(char **paths, int len);

/* remove_quote_set */
int		remove_quote_tokens(t_list *node);

/* utils.c*/
int		check_chr_not_quote_set(char *str, char c); // 반환 자료형 수정 char -> int
int		search_chr_in_str(char *str, char c); // 반환 자료형 수정 char -> int
int		are_all_characters_same(char *str, char c); // 반환 자료형 수정 char -> int
char	*get_exit_no(void);
char	**modify_least_matched_pattern(char **f_list, char *memo);

/*utils2.c*/
char	**change_system_error_msg(void);
char	*search_value_using_key(t_path *path, char *src);
char	*copy_conditional_index_range(char *str, int idx, int end, char c);
char	*copy_index_range(char *str, int idx, int end);
int		ck_part_of_special_chr(int c);

/* utils3.c*/
char	*copy_index_range_jump_quote(char *str, int idx, int end);
char	**remove_all_same_str(char **str, char c);
int		cnt_valid_split_point_chr_in_quote_set(char *path, char c, int quote);

/* util_as_file1.c */
char	**take_filenames_basic(struct dirent *entry, DIR *dir, int len);
char	**open_n_read_filenames(char *path, int len);
int		count_file_in_directory(char *path);

/* util_as_file2.c */
int		change_only_wildcard_token(t_list *node);
char	**get_root_filelist(void);
char	**get_path_filelist(char *path);
char	**get_current_filelist(void);

/* open_directory1.c */
char	**open_path_low_rank(char **path);
char	**open_root_directory(char *str, int p_len);
char	**open_wildcard_directory(char *path);
char	**open_current_directory(char *path);
char	**open_multi_directory(char *path, char **f_list);

/* open_directory2.c */
char	**split_last_slash_path(char *path);
char	**join_path_n_f_list(char **f_list, char **div);

/* open_directory3.c */
char	**div_f_list_on_slash(char **f_list, char **save);
int		increase_idx_in_quote_set(char *path, char c, int idx, int quote);
char	**take_pattern_in_path(char *path, char **div, int len, char c);
char	**quote_conitional_split(char *path, char c);
char	**matching_wildcard_pattern(char *path, char **tmp, char *copy);

/* mapping_pattern_start_n_center_filename.c */
int		compare_squence_word1(char *f_list, int idx, char **path, int *row);
int		matching_fisrt_pattern(char *f_list, char **path);
char	**mapping_pattern_start_filname(char **path, char **f_list);
int		matching_center_pattern(char *f_list, char **path);
char	**mapping_center_filename(char **path, char **f_list);

/* mapping_pattern_last_filename.c */
int		compare_reverse_word(char *f_list, int idx, char **path, int *row);
int		matching_last_pattern(char *f_list, char **path);
char	**mapping_pattern_last_filname(char **path, char **f_list);

/* mapping_pattern_side_filename.c */
int		compare_squence_word2(char *f_list, int idx, char **path, int *row);
int		matching_side_pattern(char *f_list, char **path);
char	**mapping_pattern_side_filname(char **path, char **f_list);

/* mapping_pattern_filename.c */
char	**extract_path_in_f_list(char **f_list, char *path, int len);
int		count_path_in_f_list(char **f_list, char *path);
char	**mapping_pattern_filename(char *path, char **f_list);

/* othoer_functions.c*/
int		count_only_single_chr_value_in_2d_arr(char **str, int row, char c);
int		is_token_all_null_after_join(t_tmp *tmp);

/* initialize_meta_token.c*/
t_path	*make_t_path(void);
t_data	*initialize_meta_token(char **envp);
int		mn_split(t_data *meta, char **str, char c);
void	free_exec_linked_list(t_cmd_list *list);
int		run(t_data *meta);
int		rutin_free(t_data *meta, char *str);
void	add_history_and_free(char **str);
void	normalize_cmd(t_data *meta);


#endif
