/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_character_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:46:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/09 13:05:44 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_out_redirection(const char *str, int index)
{
	int start_index;

	start_index = index;
	while (str[index] == '>')
		index++;
	return (index - start_index);
}

int check_in_redirection(const char *str, int index)
{
	int start_index;

	start_index = index;
	while (str[index] == '<')
		index++;
	return (index - start_index);
}

int check_ampersand(const char *str, int index)
{
	int start_index;

	start_index = index;
	while (str[index] == '&')
		index++;
	return (index - start_index);
}

int check_vartical_var(const char *str, int index)
{
	int start_index;

	start_index = index;
	while (str[index] == '|')
		index++;
	return (index - start_index);
}
int check_operator_set(char const *str, int index)
{
	if (str[index] == '|' || str[index] == ' ')
		return (1);
	if (str[index] == '<' || str[index] == '>')
		return (1);
	if (str[index] == '&' && str[index + 1] == '&')
		return (1);
	return (0);
}