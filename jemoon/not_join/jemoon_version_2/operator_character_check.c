/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_character_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:46:09 by jahong            #+#    #+#             */
/*   Updated: 2025/01/20 17:49:56 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_out_redirection(const char *str, int index)
{
	int	start_index;

	start_index = index;
	while (str[index] == '>')
		index++;
	return (index - start_index);
}

int	check_in_redirection(const char *str, int index)
{
	int	start_index;

	start_index = index;
	while (str[index] == '<')
		index++;
	return (index - start_index);
}

int	check_ampersand(const char *str, int index)
{
	int	start_index;

	start_index = index;
	while (str[index] == '&')
		index++;
	return (index - start_index);
}

int	check_vartical_bar(const char *str, int index)
{
	int	start_index;

	start_index = index;
	while (str[index] == '|')
		index++;
	return (index - start_index);
}

int	check_operator_set(char const *str, int index)
{
	if (str[index] == '|' || str[index] == ' ')
		return (1);
	if (str[index] == '<' || str[index] == '>')
		return (1);
	if (str[index] == '&' && str[index + 1] == '&')
		return (1);
	return (0);
}
