/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:36:58 by jemoon            #+#    #+#             */
/*   Updated: 2024/12/30 13:38:44 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
void quote_parser(char const *str, int *index, t_list **words)
{
	int	start_index;
	char *word_line;

	start_index = (*index) + 1;
	if (str[*index] == '\"')
	{
		(*index)++;
		while (str[*index] != '\0' && str[*index] != '\"')
			(*index)++;
		if (str[*index] == '\"')
		{
			if (start_index == (*index))
				return ;
			word_line = extract_word(str, start_index, *index - 1);
			if (word_line == NULL)
				return ;
			make_node(words, word_line);
        	(*index)++;
		}
    }
    else if (str[*index] == '\'')
    {
		(*index)++;
		while (str[*index] != '\0' && str[*index] != '\'')
			(*index)++;
		if (str[*index] == '\'')
		{
			if (start_index == (*index))
				return ;
			word_line = extract_word(str, start_index, *index - 1);
			if (word_line == NULL)
				return ;
			make_node(words, word_line);
        	(*index)++;
		}
	}
	else
		return;
}


int	check_quote(char const *str, int start_index, int index)
{
	int i;

	i = 0;
	while (start_index < index)
	{
		if (str[start_index] == '\'' || str[start_index] == '\"')
			return (i);
		start_index++;
		i++;
	}
	return (-1);
}

char *check_quote_line(char const *str, int start_index, int *index)
{
	int	check_point;
	int check_plag;
	int str_len;

	str_len = start_index;
	check_plag = 1;
	check_point = check_quote(str, start_index, *index);
	if (check_point == -1)
	{
		printf("no 쿼터 index =  [%d], start_index =  [%d], str_len = [%d] \n", *index, start_index, str_len);
		return (extract_word(str, start_index, *index));
	}
	else
	{
		while (str[str_len] != 32 && check_plag % 2 != 0)
		{
			str_len++;
			//(*index)++;
			printf("index =  [%d], start_index =  [%d], str_len = [%d] \n", *index, start_index, str_len);
			if (str[str_len] == '\"')
			{
				check_plag++;
			}
		}
		str_len++;
		//(*index) +=  str_len - start_index;
		//(*index)++;
		return (extract_word(str, start_index, str_len));
	}
}

*/

void	parsor(char const *str, int *start_index, int *index)
{
	int	plag_quote_d;
	int plag_quote_s;

	plag_quote_d = 0;
	plag_quote_s = 0;
	while (str[*index])
	{
		if (plag_quote_s == 0  && str[*index] == '\"')
		{
			(*index)++;
			plag_quote_d = 1;
		}
		else if (plag_quote_d == 0 && str[*index] == '\'')
		{
			(*index)++;
			plag_quote_s = 1;
		}
		else if (str[*index] == '|')
			return ;
		else if (str[*index] == '\"' && plag_quote_d == 1)
			return ;
		else if (str[*index] == '\'' && plag_quote_s == 1)
			return ;
		else if (str[*index] == '<' || str[*index] == '>')
			return ;
		else if (str[*index] == 32 && (plag_quote_d == 1 || plag_quote_s == 1))
		{
			(*index)++;
			continue;
		}
		else if (str[*index] == 32)
			return ;
		else
			(*index)++;
	}	
}