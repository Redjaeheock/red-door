/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:04:08 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/15 12:05:09 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	char	*str;
}	t_data;

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	t_data	*data = (t_data *)context;

	if (signum == SIGINT)
	{
		printf("Signal %d caught! Cleaning up...\n", signum);
		free(data->str);
		printf("Memory freed. Exiting program.\n");
		exit(0);
	}
}

int	main()
{
	struct sigaction	sa;
	t_data				data;
	int					i;

	data.str = malloc(11);
	if (!data.str)
	{
		perror("malloc failed");
		return (1);
	}
	data.str[10] = '\0';
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		free(data.str);
		return (1);
	}
	i = 0;
	while (1)
		printf("Running [%d]...\n", i++);
	return (0);
}
