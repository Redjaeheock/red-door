/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/18 15:18:04 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_pwd(t_data *meta)
{
	char	*str;

	if (ft_strcmp(meta->exec_cmd->str[0], "pwd") != 0)
		return ;
	str = ft_strdup(meta->pwd);
	if (str == NULL)
		return ;
	printf("%s\n", str);
	free(str);
}
