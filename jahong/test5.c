/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:26:20 by jahong            #+#    #+#             */
/*   Updated: 2024/12/30 21:07:07 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av, char **envp)
{
    char *str;
    char **arr;

    str = readline("");
    printf(">>> %s\n", str);
    arr = (char **)malloc(sizeof(char*) * 2);
    arr[0] = NULL;
    arr[1] = NULL;

    if (execve("/usr/bin/ls", arr, envp) == -1)
        printf("%s: command not found\n", str);
    return (0);

    
}