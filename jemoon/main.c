/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:40:49 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/07 11:32:03 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *token_type_to_str(t_tokentype type)
{
    if (type == NONE) {
        return "NONE";
    } else if (type == PIPE) {
        return "PIPE";
    } else if (type == REDIRECTION) {
        return "REDIRECTION";
    } else if (type == IN_REDEC) {
		return "IN_REDEC";
	} else if (type == OUT_REDEC) {
		return "OUT_REDEC";
	} else if (type == GR_REDEC) {
		return "GR_REDEC";
	} else if (type == HEREDOC) {
		return "HEREDOC";
	} else if (type == CMD) {
        return "CMD";
    } else if (type == OPTION) {
        return "OPTION";
    } else if (type == ARG) {
        return "ARG";
    } else {
        return "UNKNOWN";
    }
}

void replace_char(char *str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i] != '\0')
    {
        if (str[i] == 32 || str[i] == 9 || str[i] == 10)
            str[i] = 20;
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    char		*str;
    t_list 		*tokens;
    t_list		*tmp; // 출력확인용
	//t_env_list	*env_list; // 환경변수 내놔

	tokens = NULL;
    tmp = tokens; // 출력확인용
    while(1)
    {
        str = readline("bash : ");
        if (str[0] == '\0')
            continue;;
        tokens = mn_split(str + skip_leading_ifs(str));
		tmp = tokens;
		tpye_init(&tokens);
        while (tokens != NULL) // 확인용
        {
            printf("%s, [%s]\n", tokens->token, token_type_to_str(tokens->type));
            tokens = tokens->next;
        }
        tokens = tmp; // 확인 후 다시 원 위치
		validate_bash_syntax(&tokens);
        tokens = tmp; // 유효성 검사가 끝난 후 원 위치
        //lexer_n_parse(tokens);
        //run_process(tokens);
        free_linked_list(tokens);
		//add_history(str);
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
