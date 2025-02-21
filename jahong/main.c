/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 05:10:55 by jahong            #+#    #+#             */
/*   Updated: 2025/02/21 20:44:27 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_words(char const *str, char c)
{
	t_list	*words;
	int		index;

	words = NULL;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '|')
			index = pipe_div(&words, str, index, c);
		else if (str[index] == '<')
			index = in_redirec_div(&words, str, index, c);
		else if (str[index] == '>')
			index = out_redirec_div(&words, str, index, c);
		else if (str[index] == '&')
			index = ampersand_div(&words, str, index, c);
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

int	check_operator_v2(const char *str, int index)
{
	int	num;

	if (str[index] == '<')
	{
		num = check_in_redirection(str, index);
		if (num == 3)
			return (error_syntax("<"));
		else if (num >= 4)
			return (error_syntax("<<"));
	}
	else if (str[index] == '>')
	{
		num = check_out_redirection(str, index);
		if (num == 3)
			return (error_syntax(">"));
		else if (num >= 4)
			return (error_syntax(">>"));
	}
	return (1);
}

int	check_operator_v1(const char *str, int index)
{
	if (str[index] == '|')
	{
		if (check_vartical_bar(str, index) == 1)
			return (error_syntax("|"));
		else
			return (error_syntax("||"));
	}
	else if (str[index] == '&')
	{
		if (check_ampersand(str, index) == 1)
			return (error_syntax("&"));
		else
			return (error_syntax("&&"));
	}
	else if (str[index] == '<' || str[index] == '>')
		return (check_operator_v2(str, index));
	return (1);
}

int	mn_split(t_data *meta, char **str, char c)
{
	t_list	*tokens;
	int		cmd_flag;

	if (*str == NULL)
		return (-1);
	if ((*str)[0] == '\0')
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	if (c == 'c')
	{
		cmd_flag = check_operator_v1(*str, 0);
		if (cmd_flag == -1)
			return (-1);
	}
	tokens = split_words(*str, c);
	if (tokens == NULL)
		return ((free(*str), -1));
	if (substitute_tokens(meta, tokens, c) == 0)
		return ((free(*str), free_t_list(tokens), 0));
	meta->tokens = tokens;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	*meta;
	t_list	*tmp; // 출력확인용
	int	row;
	int	fd;

	meta = initialize_meta_token(envp);
	while(1)
	{
		// if (meta->stdin_flag == -1)
		// {
			
		// 	fd = open("/dev/tty", O_RDONLY);
		// 	dup2(fd, 0);
		// 	//close(fd);
		// }
		str = readline("bash : ");
		if (str == NULL)
			break ;
		if (mn_split(meta, &str, 'c') < 1)
			continue ;
		tmp = meta->tokens;
		while (tmp != NULL) // 확인용
		{
			row = 0;
			printf("final check key = %s\n", tmp->key);
			printf("final check token = %s\n", tmp->token);
			if (tmp->f_list == NULL)
				printf("final check f_list = (NULL)\n");
			while (tmp->f_list != NULL && tmp->f_list[row] != NULL)
			{
				printf("final check filelist[%d] = %s\n", row, tmp->f_list[row]);
				row++;
			}
			tmp = tmp->next;
		}
		//play(meta);
		tmp = meta->tokens;
		if (ft_strcmp(tmp->token, "<<") == 0)
		{
			meta->heredoc = 1;
			if (here_doc(meta, tmp->next) == 0)
			{
				if (meta->stdin_flag == -1)
					unlink_files(meta->tokens);
			}
			meta->heredoc = 0;
		}
		meta->tokens = free_t_list(meta->tokens);
//		add_history(str);
		free(str);
		// printf("\n");
	}
	free_meta_token(meta);
	return (0);
}

// mini shell parsing을 통해서, 들어온 인자값들을 우선 정제시킬 필요가 있음.
// 싱글쿼터, 더블쿼터가 들어왔을 때, 쓸모없는 글들을 탈락시키고, 유요한 값들만 문자열.
// 전달된 유요한 값이 빌트인이면, 빌트인으로 들어가서 작동
// 아닐 시, 환경변수를 가져와 execve 적용.
//
// 1. 어쨌든 공백 기준으로 1차적인 토큰라이져를 한다.
// 2. 메타캐리터의 유뮤 파악, 있을 시, 토큰화
// 3. 싱글쿼터나 더블쿼터가 왔을 때, 전체적인 쿼터의 개수를 파악, 개수가 홀수이면 -> error (유효하지 않는 인자 값),
	//유요할 때, 가장 밖같 쿼터 기준으로 인자값 던전달
//
// 4. 파씽은 인벨리드한 명령어 구조일 때만 전달, 명령어가 이상하더라도 전달.->
	//passing 처리된 명령어를 던지고 aceess나 빌트인에 해당하지 않을경우 error
//
// echo "This is time" = This is time
// echo "This is 'time'" = This is 'time'
// echo 'This is "time"' = This is "time"
// ehco 'THis is 'time'' = This is time
// ehco "This is "time"" = THis is time