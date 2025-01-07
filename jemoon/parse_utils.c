/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:30:59 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/02 11:13:18 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_leading_ifs(char *str)
{
	int	idx;

	idx = 0;
	if (str[idx] != 32)
		return (0);
	while (str[idx] == 32)
		idx++;
	return (idx);
}
