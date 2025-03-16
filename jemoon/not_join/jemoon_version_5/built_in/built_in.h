/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:00:31 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 11:12:56 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../minishell.h"
# include "../syntax/syntax.h"

/* cd */
/* cd_frist_utils.c */
int		set_null_by_key(t_path **exp, char *key);
int		set_value_by_key(t_path **exp, char *key, char *value);
int		set_free_by_key(t_path **exp, char *key);
int		set_oldpwd(t_path *temp, char *str);
void	redefine_export(t_path	**exp, char *home);

/* cd_frist.c */
void	cd_home(t_data *meta);

/* cd_rest_absolute.c */
int		is_absolute_path(char *dir);
char	*get_absolute_path(char **sp_dir);

/* cd_rest_relative.c */
char	*get_relative_path(t_data *meta, char **sp_dir);

/* cd_rest_utils.c */
int		start_c(char *str, char c);
int		is_current_dir(char *str);
int		is_parent_dir(char *str);
char	*redefine_pwd(t_data *meta, char *dir);
char	*set_dir(t_data *meta, char *str);

/* cd_rest.c */
void	cd_rest(t_data *meta, char *str);

/* cd_utils_path.c */
int		count_slash(char *str, char c);
int		count_back_path_len(char *str, int slash_len);
char	*remove_back_path(char *pwd, int len);
char	*add_path(char *pwd, char *dir);
char	*back_path(char *pwd);

/* cd_utils.c */
char	*get_env(t_path *env, char *home);
int		find_node(t_path *env, char *key);

/* cd.c */
void	minishell_cd(t_data *meta);

/* check_built_in_cmd */
/* check_built_in_cmd.c */
int		check_built_in_cmd(char *cmd, char *exec_cmd);

/* echo */
/* echo.c */
int		check_option_n(char *str);
void	minishell_echo(t_cmd_list **exec_cmd);

/* env */
/* env.c */
void	minishell_env(t_data *meta);

/* exit */
/* exit.c */
void	minishell_exit(t_data *meta);

/* export */
/* export_first.c */
void	frist_export(t_data *meta);

/* epxort_list_utils.c */
int		ft_lstsize(t_path *lst);
t_path	*add_export(char *str);
void	add_back_export_linked_list(t_path **old_export, t_path *new);

/* export_rets_utils.c */
int		search_special_characters(char *str);
void	update_node(t_path **old_exp, t_path *prev, \
	t_path *current, t_path *new_node);
int		check_key(t_path **old_exp, t_path *export_add);
int		search_equal(char *str);
void	process_export_entry(t_data *meta, \
	t_path *export_add, t_path *env_add, int equal);

/* export_rest.c */
void	rest_export(t_data *meta, int export_len);

/* export_sort_uitls.c */
int		ft_test(char *s1, const char *s2);

/* export_sort.c */
void	swap_first_two(t_path **exp);
void	swap_middle_two(t_path *exp_prev);
void	swap_export(t_path **exp, t_path *exp_prev);
void	bubble_sort(t_path **exp, int *swapped);
void	sort_export(t_path **exp);

/* export_utils.c */
int		char_arr_len(char **array);

/* export.c */
void	minishell_export(t_data *meta);

/* pwd */
/* pwd.c */
void	minishell_pwd(t_data *meta);

/* unset */
/* unset_export*/
void	remove_node(t_path **exp, t_path *prev, t_path *current);
int		unset_key(t_path **exp, char *str);
void	unset_export(t_data *meta, int unset_len);

/* unset_utils.c */
int		search_special_characters_unset(char *str);

/* unset.c */
void	minishell_unset(t_data *meta);

/* builtin.c*/
void	builtin(t_data *meta);

#endif
