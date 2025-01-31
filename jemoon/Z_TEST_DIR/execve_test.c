/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:41:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/27 14:50:31 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 3);
	arr[0] = "env";
	arr[1] = "ls";
	arr[2] = NULL;
	if (execve("/usr/bin/env", arr, envp) == -1)
		printf("command not found\n");
	return (0);
}
