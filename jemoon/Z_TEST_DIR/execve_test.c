/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:41:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/10 11:58:19 by jemoon           ###   ########.fr       */
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
	arr[1] = "/home/jemoon/42/red-door/jemoon/jemoon_version_5/*";
	arr[2] = NULL;
	if (execve("/bin/ls", arr, envp) == -1)
		printf("command not found\n");
	return (0);
}
