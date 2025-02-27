/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:41:12 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 10:45:53 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

int	char_arr_len(char **array)
{
	int	len;

	len = 0;
	if (array == NULL)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}
