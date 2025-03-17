/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:33:49 by jahong            #+#    #+#             */
/*   Updated: 2025/03/14 15:05:27 by jemoon           ###   ########.fr       */
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
