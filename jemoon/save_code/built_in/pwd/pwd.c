/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 22:06:24 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/24 13:33:09 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	minishell_pwd(t_data *meta)
{
	char	*str;

	str = ft_strdup(meta->pwd);
	if (str == NULL)
		return ;
	printf("%s\n", str);
	free(str);
}
