/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:33:49 by jahong            #+#    #+#             */
/*   Updated: 2025/03/21 20:53:31 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wranning_msg(char *eof)
{
	printf("bash: warning: here-document ");
	printf("at line 62 delimited ");
	printf("by end-of-file (wanted `%s')\n", eof);
	g_ws = 0;
}

void	exceve_error_msg(t_cmd_list *cmd, char *path)
{
	if (access(path, X_OK) != 0)
		printf("bash: %s: %s\n", path, strerror(2));
	else
	{
		if (ft_strcmp(cmd->str[0], "") == 0)
		{
			free(cmd->str[0]);
			cmd->str[0] = strdup("\'\'");
			printf("bash: %s: %s\n", cmd->str[0], strerror(2));
		}
		else
			printf("bash: %s: %s\n", cmd->str[0], strerror(2));
	}
}
