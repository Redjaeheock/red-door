/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_character_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:46:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/02 11:52:53 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_vartical_var(const char *str, int index)
{
	int start_index;

	start_index = index;
	while (str[index] == '|')
		index++;
	return (index);
}
int operator_check(char const *str, int index)
{
	printf("check operator\n");
	if (str[index] == '|' || str[index] == '>')
		return (1);
	if (str[index] == '<' || str[index] == ' ')
		return (1);
	if (str[index] == '&' && str[index + 1] == '&')
		return (1);
	return (0);
}