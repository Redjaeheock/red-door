/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:22:18 by jahong            #+#    #+#             */
/*   Updated: 2025/01/03 14:47:09 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int error_syntax(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (ft_strncmp(str, "||", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `||'\n");
	else if (ft_strncmp(str, "&", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `&'\n");
	else if (ft_strncmp(str, "&&", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `&&'\n");
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		printf("bash: syntax error near unexpected token `>>'\n");
	return (-1);
}