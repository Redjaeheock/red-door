/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:33:38 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/26 20:01:42 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

t_list	*last_tokens(t_list *exec_cmd)
{
	t_list		*temp;

	temp = exec_cmd;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	check_last_tokens(t_list *exec_cmd)
{
	int			i;
	t_list		*temp;

	i = 0;
	temp = exec_cmd;
	if (temp == NULL)
		return (0);
	while (exec_cmd->next != NULL)
		exec_cmd = exec_cmd->next;
	if (AND <= exec_cmd->type && exec_cmd->type <= PIPE)
		i = 1;
	exec_cmd = temp;
	return (i);
}

void	combine_strings(char *return_str, char *str, char *add_str)
{
	int	i;
	int	j;
	int	str_len;
	int	add_str_len;

	i = 0;
	j = 0;
	str_len = ft_strlen(str);
	add_str_len = ft_strlen(add_str);
	while (i < str_len + add_str_len + 1)
	{
		if (i < str_len)
			return_str[i] = str[i];
		else if (i == str_len)
			return_str[i] = 32;
		else if (j < add_str_len)
		{
			return_str[i] = add_str[j];
			j++;
		}
		i++;
	}
	return_str[i] = '\0';
}

char	*make_str(char *str, char *add_str)
{
	int		str_len;
	int		add_str_len;
	char	*return_str;

	str_len = ft_strlen(str);
	add_str_len = ft_strlen(add_str);
	return_str = (char *)malloc(sizeof(char) * (str_len + add_str_len + 2));
	if (return_str == NULL)
		return (str);
	combine_strings(return_str, str, add_str);
	free(str);
	free(add_str);
	return (return_str);
}

char	*add_readline(t_data *meta, char *str)
{
	char		*add_str;
	int			i;
	t_list		*tmp;

	while (check_last_tokens(meta->tokens) == 1)
	{
		meta->heredoc = 1;
		tmp = last_tokens(meta->tokens);
		add_str = readline("> ");
		if (add_str == NULL)
			return (add_readline_signal(meta, str));
		meta->heredoc = 0;
		i = mn_split(meta, &add_str, 'c');
		if (i == 0)
			break ;
		str = make_str(str, add_str);
		if (i == -1)
			return (str);
		add_readline_trade_exec_cmd(meta, tmp, str);
		if (meta->tokens == NULL)
			return (str);
		if (validate_bash_syntax(&meta->tokens) == -1)
			return (str);
	}
	return (str);
}
