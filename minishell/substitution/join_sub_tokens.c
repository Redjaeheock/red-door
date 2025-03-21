/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_sub_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:06:45 by jahong            #+#    #+#             */
/*   Updated: 2025/03/22 20:10:03 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_null_string_n_null_point(t_cmd_list *cmd, char *s, int row)
{
	if (cmd->str[row][0] == '$' && s[0] == '\0')
	{
		free(cmd->str[row]);
		cmd->str[row] = change_null_string();
		if (cmd->str[row] == NULL)
			return (0);
	}
	else if (ft_strcmp(s, "\"\"") == 0)
	{
		free(cmd->str[row]);
		cmd->str[row] = change_null_string();
		if (cmd->str[row] == NULL)
			return (0);
	}
	else if (cmd->str[row] != NULL)
	{
		free(cmd->str[row]);
		cmd->str[row] = ft_strdup(s);
		if (cmd->str[row] == NULL)
			return ((memory_alloc_error(), 0));
	}
	return (1);
}

int	conditional_jump_t_tmp(t_tmp **tmp, int flag, int quote)
{
	if (flag != 1 && (*tmp)->value == NULL && (*tmp)->key[0] == '$')
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	else if ((*tmp)->key != NULL && (*tmp)->key[0] == '$')
	{
		if ((quote == 0 && ft_strlen((*tmp)->key) == 1) && (*tmp)->next != NULL)
		{
			(*tmp) = (*tmp)->next;
			return (1);
		}
	}
	return (0);
}

char	*alloc_tokens_token(t_tmp *tmp, char c)
{
	char	*str1;
	char	*str2;
	int		quote;

	str1 = NULL;
	quote = 0;
	while (tmp != NULL)
	{
		if (tmp->key != NULL && tmp->key[0] == '"')
			quote = check_quote_pair(tmp->key[0], quote);
		if (tmp->value == NULL && tmp->key[0] != '$')
			str2 = ft_strjoin_v2(str1, tmp->key);
		else if (c == 'c' && conditional_jump_t_tmp(&tmp, 1, quote) == 1)
			continue ;
		else
			str2 = ft_strjoin_v2(str1, tmp->value);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		tmp = tmp->next;
	}
	return (str1);
}

char	*alloc_tokens_key(t_tmp *tmp, char c)
{
	char	*str1;
	char	*str2;
	int		flag;
	int		quote;

	str1 = NULL;
	quote = 0;
	flag = is_token_all_null_after_join(tmp);
	while (tmp != NULL)
	{
		if (tmp->key != NULL && tmp->key[0] == '"')
			quote = check_quote_pair(tmp->key[0], quote);
		if (c == 'c' && conditional_jump_t_tmp(&tmp, flag, quote) == 1)
			continue ;
		str2 = ft_strjoin_v2(str1, tmp->key);
		if (str1 != NULL)
			free(str1);
		if (str2 == NULL)
			return (NULL);
		str1 = str2;
		tmp = tmp->next;
	}
	return (str1);
}

int	join_sub_tokens(t_cmd_list *cmd, t_tmp *node, char c, int fd)
{
	char	*str;

	if (c == 'c')
	{
		cmd->f_list[fd] = alloc_tokens_key(node, c);
		if (cmd->f_list[fd] == NULL)
			return (0);
		str = alloc_tokens_token(node, c);
		if (str == NULL)
			return (0);
		if (change_null_string_n_null_point(cmd, str, fd) == 0)
			return ((free(str), 0));
	}
	else
	{
		str = alloc_tokens_token(node, c);
		if (str != NULL)
			ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	return ((free(str), 1));
}
