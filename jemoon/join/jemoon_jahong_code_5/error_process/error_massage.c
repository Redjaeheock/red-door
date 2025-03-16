/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:33:49 by jahong            #+#    #+#             */
/*   Updated: 2025/02/21 20:34:09 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wranning_msg(char *eof)
{
	printf("bash: warning: here-document ");
	printf("at line 62 delimited ");
	printf("by end-of-file (wanted `%s')\n", eof);
}
