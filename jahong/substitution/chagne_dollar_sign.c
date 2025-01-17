/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chagne_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:35:13 by jahong            #+#    #+#             */
/*   Updated: 2025/01/17 16:02:49 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_current_process_pid(void)
{
	char	*tmp;
	char	*nums;
	int		len;
	int		idx;

	nums = "54321"; //프로세스 ID itoa 처리
	len = ft_strlen(nums);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	idx = 0;
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
char	*copy_env_value(char *str)
{
	char	*tmp;
	int		idx;
	int		len;

	idx = 0;
	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (str[idx] != '\0')
	{
		tmp[idx] = str[idx];
		idx++;
	}
	tmp[idx] = '\0';
	return (tmp);
}