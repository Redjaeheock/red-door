/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:19 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/31 16:51:41 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char * path = "";
	char dir[30] = "Current Directory: ";

	write(1, dir, sizeof(char) * strlen(dir));
	if ( system("pwd") == -1)
	{
		perror("command failed!\n");
	}
	int ch = chdir(path);
	if( ch == 0 )
	{
		printf("Change directory\n");
	}else
	{
		printf("Failed change directory!\n");
	}
	write(1, dir, sizeof(char) * strlen(dir));
	if ( system("pwd") == -1)
	{
		perror("command failed!\n");
	}
	return (0);
}
