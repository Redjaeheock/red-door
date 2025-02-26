/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:38:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/25 16:59:44 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# define _POSIX_C_SOURCE 200809L 

# include "../minishell.h"

/* exec_commads */
/* exec_commads_liked_list_2.c */
void		exec_make_node_2(t_cmd_list **exec_cmd, char **string_array, \
			t_tokentype plag_pipe, t_tokentype plag_redi);
void		exec_add_key_str(t_cmd_list **exec_cmd, char *str);

/* exec_commads_liked_list.c */
void		free_double_string_array(char **str);
void		free_exec_linked_list(t_cmd_list *list);
t_cmd_list	*create_exec_linked_list(char **str, \
t_tokentype plag_pipe, t_tokentype plag_redi);
void		add_back_exec_linked_list(t_cmd_list **exec_cmd, \
t_cmd_list *new);
void		exec_make_node(t_cmd_list **exec_cmd, char **string_array, \
t_tokentype plag_pipe, t_tokentype plag_redi);

/* exec_commads_size_2.c */
int			handle_redirection_case(t_list *tokens, int *check_redi, \
			t_tokentype *plag_redi);
int			handle_pipe_case(t_list *tokens, t_tokentype *plag_pipe);
int			handle_previous_redirection(t_list *tokens, int *check_redi);
int			calculate_array_size(t_list *tokens);
int			get_double_string_array_size(t_list *tokens, int *check_redi, \
			t_tokentype *plag_pipe, t_tokentype *plag_redi);

/* exec_commads_size.c  */
int			check_redirection_size(t_list **tmp, int *array_size);
int			get_first_double_string_array_size(t_list **tmp);
int			get_rest_double_string_array_size(t_list **tmp);

/* get_exec_commads_2.c */
char		*set_string_2(char *tokens, int cmd_size);
//void		fill_string_array_2(char **string_array, \
//			t_list **tokens, int cmd_size);
char		**set_string_array_2(t_list **tokens, int cmd_size);
char		*get_key_string(t_list *tokens);
char		*get_key(t_list *tokens, int check_redi);
void		get_exec_cmd_2(t_list *tokens, t_cmd_list **exec_cmd);

/* get_exec_commads_2_utils.c */
void		get_commads_f_list(char **string_array, t_list **tokens, \
			int *i, int cmd_size);
void		get_commads_token(char **string_array, t_list **tokens, \
			int *i, int cmd_size);
void		get_commads_key(char **string_array, t_list **tokens, \
			int *i, int cmd_size);

/* get_exec_commads.c */
void		recycle_size(t_list *tokens, int *cmd_size, \
			t_tokentype *plag_pipe, t_tokentype *plag_redi);
char		*set_string(t_list *tokens);
void		fill_string_array(char **string_array, t_list *tokens, \
			int cmd_size);
char		**set_string_array(t_list *tokens, int cmd_size, \
			t_tokentype *plag_pipe, t_tokentype *plag_redi);
void		get_exec_commads(t_list **tokens, t_cmd_list **exec_commads, int i);

/* new_get_exec_cmd.c*/
void		new_get_exec_cmd(t_list *tokens, t_cmd_list **exec_cmd);

/* exec_commads_set_type */
/* exec_commads_set_type.c */
int			check_prev(t_cmd_list	*exec_cmd);
int			check_next(t_cmd_list	*exec_cmd);
int			check_redi(t_cmd_list	*exec_cmd);
int			check_pipe(t_cmd_list	*exec_cmd);
void		exec_cmd_set_tpye(t_cmd_list **exec_cmd);

/* pritnf_utils */
/* pritnf_utils.c */
void		printf_exec_commads(t_cmd_list *exec_commands);
const char	*token_type_to_str_1(t_tokentype type);
void		printf_tokens(t_list *tokens);

/* readline_utils */
/* readline_utils.c */
char		*handle_error(t_cmd_list **exec_cmd, char *str);
//int			check_last_tokens(t_cmd_list *exec_cmd);
int			check_last_tokens(t_list *exec_cmd);
void		combine_strings(char *return_str, char *str, char *add_str);
char		*make_str(char *str, char *add_str);
char		*add_readline(t_data *meta, char *str);

/* set_tpye */
/* set_tpye.c*/
void		is_first_node_type(t_list **tokens);
void		set_tpye(t_list **tokens);
void		tpye_init(t_list **tokens);

/* validate_syntax */
/* tread_exec_cmd.c */
int			trade_exec_cmd(t_data *meta, t_cmd_list **exec_cmd, \
			t_list **tokens, char **str);

/* validate_bash_syntax_utils.c */
int			check_is_valid_redirection(t_list **tokens);
int			check_is_valid_arg(t_list **tokens);
int			first_check_is_valid(t_list **tokens);
int			rest_check_is_valid(t_list **tokens);
int			check_is_valid(t_list **tokens, int count_cmd_line);

/* validate_bash_syntax.c*/
int			validate_bash_syntax(t_list **tokens);

/* jemoon_libft */
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_front_slash(char *s1, char *s2);

/* add code*/
int			redefine_cmd_size(t_list *tokens, int cmd_size);
void		get_commads_key_to_token(char **string_array, t_list **tokens, \
			int *i, int redifine_size);
void		get_key_to_toke(char **string_array, t_list **tokens, \
			int *i, int redifine_size);
void		fill_string_array_2(char **string_array, t_list **tokens, \
			int cmd_size, int redefine_size);
void		set_here_doc(t_data *meta, t_list *tmp);
void		operator_str_free(t_data *meta);
char		*add_readline_signal(t_data *meta, char *str);
void		add_readline_trade_exec_cmd(t_data *meta, t_list *tmp, char *str);


#endif
