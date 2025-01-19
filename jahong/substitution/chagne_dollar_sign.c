/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chagne_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:35:13 by jahong            #+#    #+#             */
/*   Updated: 2025/01/19 14:46:04 by jahong           ###   ########.fr       */
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
char *copy_split_token(char *str, int idx, int end)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = end - idx;
	if (end != ft_strlen(str))
		len++;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (sndry_alloc_err(NULL));
	while (idx < end)
	{
		tmp[i] = str[idx];
		idx++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}