/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:41:18 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/02 11:47:30 by jemoon           ###   ########.fr       */
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

	str = readline("> : ");
	printf(">>> %s\n", str);
	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = "<<<";
	arr[1] = NULL;
	if (execve("/usr/bin/grep", arr, envp) == -1)
		printf("%s: command not found\n", str);
	return (0);
}
