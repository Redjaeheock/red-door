/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/11 13:08:10 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_pwd(t_data *meta, t_cmd_list *exec_cmd)
{
	char	*str;
	int		pwd_len;

	pwd_len = sndry_arr_len((void **)exec_cmd->str);
	str = ft_strdup(meta->pwd);
	if (str == NULL)
		return ;
	if (pwd_len == 2)
	{
		if (check_option(exec_cmd->str[1]) == 1)
		{
			builtin_error(exec_cmd->str[1], 31);
			free(str);
			return ;
		}
	}
	printf("%s\n", str);
	free(str);
	g_ws = 0;
}
