/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:35:13 by jahong            #+#    #+#             */
/*   Updated: 2025/01/23 10:49:04 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_null_string(void)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 1);
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	tmp[0] = '\0';
	return (tmp);
}
char	*copy_current_process_pid(void)
{
	char	*nums;
	char	*tmp;
	int		idx;
	int		len;

	nums = "54321"; //프로세스 ID itoa 처리
	idx = 0;
	len = ft_strlen(nums);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (nums[idx] != '\0')
	{
		tmp[idx] = nums[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}