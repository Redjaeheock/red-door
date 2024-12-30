/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 05:11:01 by jahong            #+#    #+#             */
/*   Updated: 2024-12-29 05:11:01 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

char	*extract_word(char const *str, int start_index, int index)
{
	char	*word_line;
	int		idx;

	idx = 0;
    if (str == NULL)
        return (NULL);
	word_line = (char *)malloc(sizeof(char) * (index - start_index + 1));
	if (!word_line)
		return (NULL);
	while (start_index < index + 1 && str[start_index] != '\0')
	{
		word_line[idx] = str[start_index];
		start_index++;
		idx++;
	}
	word_line[idx] = '\0';
	return (word_line);
}
int operator_check(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
}

int string_div(t_list **words, char const *str, int index)
{
    int flag;
    int start_index;

    flag = 0;
    start_index = index;
    while (str[index] != '\0')
    {
        if (str[index] == 39 && flag == 0)
            flag = 39;
        else if (str[index] == 39 && flag != 34)
            flag = 0;
        else if (str[index] == 34 && flag == 0)
            flag = 34;
        else if ((str[index] == 34 && flag != 39))
            flag = 0;
        else if (flag == 0 && operator_check(str[index]) == 1)
        {
            index--;
            break ;
        }
        else if (str[index] == 32 && flag == 0)
            break ;
        index++;
    }
    make_node(words, extract_word(str, start_index, index));
    if (make_node == NULL)
        return (-1);
    return (index);
}

int pipe_div(t_list **words, const char *str, int index)
{
    char    *word_line;
    int     start_index;

    start_index = index;
    while (str[index] != '\0')
    {
        if (str[index] == '|')
            break ;
        index++;
    }
    word_line = extract_word(str, start_index, index);
    if (word_line == NULL)
        return (-1);
    make_node(words, word_line);
    if (make_node == NULL)
        return (-1);
    return (index);
}

int in_redirec_div(t_list **words, const char *str, int index)
{
    char    *word_line;
    int     start_index;

    start_index = index;
    while (str[index] != '\0')
    {
        if (str[index] != '<')
            break ;
        index++;
    }
    word_line = extract_word(str, start_index, index);
    if (word_line == NULL)
        return (-1);
    make_node(words, word_line);
    if (make_node == NULL)
        return (-1);
    return (index);
}

int out_redirec_div(t_list **words, const char *str, int index)
{
    char    *word_line;
    int     start_index;

    start_index = index;
    while (str[index] != '\0')
    {
        if (str[index] != '>')
            break ;
        index++;
    }
    word_line = extract_word(str, start_index, index);
    if (word_line == NULL)
        return (-1);
    make_node(words, word_line);
    if (make_node == NULL)
        return (-1);
    if (str[index] == '\0')
        index--;
    return (index);
}

t_list	*split_words(char const *str, int cmd_flag)
{
	t_list	*words;
	int		index;
	char	*word_line;

	index = 0;
	words = NULL;
	while (str[index] != '\0')
	{   
        if (str[index] == '|')
            index = pipe_div(&words, str, index);
        else if (str[index] != 32)
            index = string_div(&words, str, index);
        if (index == -1)
            return (NULL);
        else if (str[index] == '\0')
            break ;
        index++;
	}
	return (words);
}

int start_check(char c)
{
    if (c == '|')
    {
        printf("bash: syntax error near unexpected token `|'\n");
        // 에러 넘버 확인
        return (-1);
    }
    else if (c == '<' || c == '>')
        return (0);
    else
        return (1);
}

t_list *mn_split(char const *str)
{
	t_list	*words;
    int cmd_flag;

	if (!str)
		return (NULL);
    cmd_flag = start_check(str[0]);
    if (cmd_flag == -1)
        return (NULL);
	words = split_words(str, cmd_flag);
	return (words);
}

//	1. 더블 쿼터나 싱글 쿼터 중 하나가 보이면 해당 plag 지정.
//	2. 지정된 plag가 아닌 쿼터가 나온다면(IFS 값 포함, 중복 쿼터), 우선은 문자열로 처리하고 pass
//	3. 지정된 plag가 나온다면, 우선은 plag 지정해제,
//	4. 3번의 경우 곧바로 IFS가 나온다면, 해당 부분을 토큰화, 
//  	    4.1 IFS가 아닌, 쿼터나 문자 나온다면, 1~3번을 반복
// 	5. 해당 방식으로 토큰화 진행하며, 마지막 체크 할 때 IFS끝이 어디까지 있는지까지 체크. 

// 	1.문제점 = "" '' 해당 방식으로 쿼터만 있다면, 어떻게 토큰으로 던져야하나
// 	2.문제점 = "abc 방식으로 닫히지 않는 명령어는 어떻게 토큰화 해야하는가
// 	1.궁금증 = 이스케이프의 경우 리드라인은 어떻게 문자열을 담아가는지

// cmd와 리다이렉션은 제일 처음에오고, 제일 마지막
// 리다이렉션 뒤는 무조건 -> 파라미터(파일)


// index -> 