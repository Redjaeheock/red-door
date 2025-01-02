/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/01/02 10:39:51 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        else if (str[index] == '<')
            index = in_redirec_div(&words, str, index);
        else if (str[index] == '>')
            index = out_redirec_div(&words, str, index);
        else if (str[index] == '&')
            index = ampersand_div(&words, str, index);
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
    else if (c == '&')
    {

         printf("bash: syntax error near unexpected token `&'\n");
        // 에러 넘버 확인
        return (-1);

    }
    else if (c == '<' || c == '>')
        return (0);
    
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

int	main(void)
{
	char	*str;
	t_list	*tokens;
	t_list	*tmp; // 출력확인용

	while(1)
	{
		str = readline("bash : ");
		if (str[0] == '\0')
			continue;
		tokens = mn_split(str);
		tmp = tokens;
		while (tmp != NULL) // 확인용
		{
			printf("%s\n", tmp->token);
			tmp = tmp->next;
		}
       // lexer_n_parse(tokens);
        //run_process(tokens);
		free_linked_list(tokens);
//      add_history(str);
		free(str);
	}
}

// mini shell parsing을 통해서, 들어온 인자값들을 우선 정제시킬 필요가 있음.
// 싱글쿼터, 더블쿼터가 들어왔을 때, 쓸모없는 글들을 탈락시키고, 유요한 값들만 문자열.
// 전달된 유요한 값이 빌트인이면, 빌트인으로 들어가서 작동
// 아닐 시, 환경변수를 가져와 execve 적용.

// 1. 어쨌든 공백 기준으로 1차적인 토큰라이져를 한다.
// 2. 메타캐리터의 유뮤 파악, 있을 시, 토큰화\
// 3. 싱글쿼터나 더블쿼터가 왔을 때, 전체적인 쿼터의 개수를 파악, 개수가 홀수이면 -> error (유효하지 않는 인자 값), \
    유요할 때, 가장 밖같 쿼터 기준으로 인자값 던전달

// 4. 파씽은 인벨리드한 명령어 구조일 때만 전달, 명령어가 이상하더라도 전달.-> \
    passing 처리된 명령어를 던지고 aceess나 빌트인에 해당하지 않을경우 error

// echo "This is time" = This is time
// echo "This is 'time'" = This is 'time'
// echo 'This is "time"' = This is "time"
// ehco 'THis is 'time'' = This is time
// ehco "This is "time"" = THis is time
