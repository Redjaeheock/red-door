/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:42:05 by jahong            #+#    #+#             */
/*   Updated: 2025/01/16 18:47:30 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int main()
{
	char **tmp;

	tmp = (char **)malloc(sizeof(char *) * 7);
	tmp[0] = (char *)malloc(sizeof(char) * 2);
	tmp[0][0] = 'a';
	tmp[0][1] = '\0';

	tmp[1] = (char *)malloc(sizeof(char) * 2);
	tmp[1][0] = 'b';
	tmp[1][1] = '\0';

	tmp[2] = (char *)malloc(sizeof(char) * 2);
	tmp[2][0] = 'b';
	tmp[2][1] = '\0';

	tmp[3] = (char *)malloc(sizeof(char) * 1);
	tmp[3][0] = '\0';

	tmp[4] = (char *)malloc(sizeof(char) * 2);
	tmp[4][0] = 'b';
	tmp[4][1] = '\0';

	tmp[5] = (char *)malloc(sizeof(char) * 2);
	tmp[5][0] = 'b';
	tmp[5][1] = '\0';

	tmp[6] = NULL;
	free_sndry_arr((void **)tmp);
	return (0);
}