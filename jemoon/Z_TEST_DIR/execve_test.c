/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:41:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/03/14 14:04:51 by jemoon           ###   ########.fr       */
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
	arr[0] = "ls";
	arr[1] = "z/c";
	arr[2] = NULL;
	if (execve("/bin/ls", arr, envp) == -1)
		printf("bash %s 1 command not found\n", arr[0]);
	return (0);
}
