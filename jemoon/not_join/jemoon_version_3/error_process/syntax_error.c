/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:22:18 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 16:31:28 by jemoon           ###   ########.fr       */
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
	//exit no 설정
	return (-1);
}

void	error_qoute(int quote)
{
	if (quote == 1)
		printf("bash: syntax error near unexpected token '\''\n");
	else
		printf("bash: syntax error near unexpected token '\"'\n");
	//exit no 설정
	return ;
}
