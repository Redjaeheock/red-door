/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/22 14:06:16 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
char	*searching_from_envval(t_data *meta, char *str)
{
	t_path	*tmp;
	int		len;

	tmp = meta->env;
	len = ft_strlen(str);
	if (str[len - 1] == '$')
		return (copy_current_process_pid());
	if (str[0] == '$' && str[1] == '?')
		return (get_exit_no());
	while (tmp != NULL)
	{
		if (ft_strncmp(&str[1], tmp->key, ft_strlen(&str[1])) == 0)
			return (copy_env_value(tmp->value));
		tmp = tmp->next;
	}
	return (change_null_string());
}
*/

void	minishell_pwd(t_data *meta)
{
	if (ft_strcmp(meta->exec_cmd->str[0], "PWD") != 0)
		return ;
	printf("%s\n", searching_from_envval(meta, "PWD"));
}
