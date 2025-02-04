/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_commads_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:11:39 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/04 14:58:02 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../syntax.h"

char	*set_string_2(t_list *tokens, int cmd_size)
{
	int		string_len;
	char	*str;

	if (tokens->token == NULL && cmd_size == 1)
	{
		printf("이거 맞냐?[%s] [%d]\n", tokens->key, cmd_size);
		string_len = ft_strlen(tokens->key);
		str = (char *)malloc(sizeof(char) * (string_len + 1));
		if (str == NULL)
			return (NULL);
		strcpy(str, tokens->key);
		printf("값이 왜?[%s]\n", str);
		return (str);
	}
	/* 결국 해당 조건에 맞지 않은 NULL은 아래 코드에서 들어가 버림.*/
	/* 이를 해결하기 위해서는 말록을 할당하기 전에, 처리해야하고,*/
	/* NULL포인터 일때, 밖의 i값을 증가시키지 않으면서, 다음 토큰을 업데이트*/
	string_len = ft_strlen(tokens->token);
	str = (char *)malloc(sizeof(char) * (string_len + 1));
	if (str == NULL)
		return (NULL);
	strcpy(str, tokens->token);
	return (str);
}

void	fill_string_array_2(char **string_array, t_list **tokens, int cmd_size)
{
	int	i;

	i = 0;
	while (i < cmd_size)
	{
		//if ((*tokens)->token != NULL)
		//{
		string_array[i] = set_string_2(*tokens, cmd_size);
		if (string_array[i] == NULL)
			return ;
		i++;
		//}
		*tokens = (*tokens)->next;
	}
	string_array[i] = NULL;
}

char	**set_string_array_2(t_list **tokens, int cmd_size)
{
	char	**string_array;

	if (cmd_size == 0)
		return (NULL);
	string_array = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (string_array == NULL)
		return (NULL);
	printf("현재 키 값은 [] 입니다.\n");
	fill_string_array_2(string_array, tokens, cmd_size);
	return (string_array);
}

char	*get_key_string(t_list *tokens)
{
	int		malloc_len;
	char	*return_key;

	malloc_len = ft_strlen(tokens->key);
	if (malloc_len == 0)
		return (NULL);
	return_key = (char *)malloc(sizeof(char) * (malloc_len + 1));
	if (return_key == NULL)
		return (NULL);
	strcpy(return_key, tokens->key);
	return (return_key);
}

char	*get_key(t_list *tokens, int check_redi)
{
	if (check_redi == 1 && tokens)
		return (get_key_string(tokens));
	else
		return (NULL);
}

void	get_exec_cmd_2(t_list *tokens, t_cmd_list **exec_cmd)
{
	t_tokentype	plag_pipe;
	t_tokentype	plag_redi;
	int			cmd_size;
	int			check_redi;
	char		**string_array;
	char		*key;

	check_redi = 0;
	while (tokens)
	{
		plag_pipe = NONE;
		plag_redi = NONE;
		key = get_key(tokens, check_redi);
		cmd_size = get_double_string_array_size(tokens, &check_redi, \
		&plag_pipe, &plag_redi);
		printf("cmd_size [%d] 사이즈입니다. \n", cmd_size);
		if (cmd_size == 0)
		{
			tokens = tokens->next;
			continue ;
		}
		printf("현재 키 값은 [%s] 입니다.\n", key);
		string_array = set_string_array_2(&tokens, cmd_size);
		if (string_array == NULL)
			return ;
		printf("키값을 넣었습니다 \n");	
		exec_make_node_2(&(*exec_cmd), string_array, \
		plag_pipe, plag_redi);
		if (key != NULL)
			exec_add_key_str(&(*exec_cmd), key);
	}
}

// 마지막 함수 최종 마지막도 안되면 구조체로 바꾸기.
