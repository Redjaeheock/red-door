/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:05:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/13 15:08:50 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int		idx;
	char	*str;

	str = "hello world";
	if (str[0] != '\0')
		while (str[idx] != '\0')
			idx++;
}
