/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:29 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/22 16:46:42 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	char_arr_len(char **array)
{
	int	len;

	len = 0;
	if (array == NULL)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}

int	ft_lstsize(t_path *lst)
{
	int		l_size;
	t_path	*temp;

	temp = lst;
	l_size = 0;
	while (temp)
	{
		l_size++;
		temp = temp->next;
	}
	return (l_size);
}

void	swap_export(t_path **exp)
{
	t_path	*temp_head;
	t_path	*two_head;
	t_path	*last_head;

	if (ft_lstsize(*exp) == 0)
		return ;
	temp_head = *exp;
	if (temp_head->next != NULL)
	{
		two_head = temp_head->next;
		last_head = two_head->next;
		two_head->next = temp_head;
		temp_head->next = last_head;
		*exp = two_head;
	}
	return ;
}

void	sort_export(t_path *exp)
{
	t_path	*tmep;
	t_path	*tmp_i;
	t_path	*tmp_j;

	tmep = exp;
	while (tmep->next && tmep->next->next)
	{
		tmp_i = tmep;
		tmp_j = tmp_i->next;
		while (tmp_j)
		{
			if (ft_strncmp(tmp_i->value, tmp_j->value, ft_strlen(tmp_i->value)) > 0)
			{
				printf("정렬중입니다\n");
				swap_export(&tmp_i);
			}
			tmp_i = tmp_i->next;
			tmp_j = tmp_j->next;
		}
		tmep = tmep->next;
	}
}

void	minishell_export(t_data *meta)
{
	t_path	*tmp;

	tmp = meta->exp;
	if (ft_strcmp(meta->exec_cmd->str[0], "export") != 0)
		return ;
	if (char_arr_len(meta->exec_cmd->str) == 1)
	{
		sort_export(tmp);
		while (tmp != NULL)
		{
			printf("declare -x %s\n", tmp->set);
			tmp = tmp->next;
		}
	}
	tmp = meta->exp;
}
	// exec_cmd의 길이가 1이라면, 정렬 후 export 출력
	// exec_cmd의 길이가 2 이상이라면, 	export에 추가.
	// 단 +나 특수문자가 들어올 경우, 에러 출력하고, 다음에 들어오는 문자열 인자는
	// export에 추가.
