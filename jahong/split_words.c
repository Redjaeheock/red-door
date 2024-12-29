/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:22:37 by jemoon            #+#    #+#             */
/*   Updated: 2024/12/27 15:55:57 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*extract_word(char const *str, int start_index, int index)
{
	char	*word_line;
	int		idx;

	idx = 0;
	word_line = (char *)malloc(sizeof(char) * (index - start_index + 1));
	if (!word_line)
		return (NULL);
	while (start_index < index)
	{
		word_line[idx] = str[start_index];
		start_index++;
		idx++;
	}
	word_line[idx] = '\0';
	return (word_line);
}

t_list	*split_words(char const *str)
{
	t_list	*words;
	int		index;
	int		start_index;
	char	*word_line;

	index = 0;
	start_index = 0;
	words = NULL;
	while (str[index] != '\0')
	{
		if (str[index] == 32 || str[index] == 9 || str[index + 1] == '\0')
		{
			if (str[index + 1] == '\0')
				index++;
			word_line = extract_word(str, start_index, index);
			if (word_line == NULL)
				return (NULL);
			make_node(&words, word_line);
			if (words == NULL)
				return (NULL);
			start_index = index + 1;
		}
		index++;
	}
	return (words);
}

t_list *mn_split(char const *str)
{
	t_list	*words;

	if (!str)
		return (NULL);
	words = split_words(str);
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