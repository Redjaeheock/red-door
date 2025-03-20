/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:35:13 by jahong            #+#    #+#             */
/*   Updated: 2025/03/20 16:26:09 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_current_process_pid(t_data *meta)
{
	char	*nums;
	char	*tmp;
	int		idx;
	int		len;

	nums = ft_itoa(meta->ppid);
	if (nums == NULL)
		return (memory_alloc_error());
	// idx = 0;
	// len = ft_strlen(nums);
	// tmp = (char *)malloc(sizeof(char) * (len + 1));
	// if (tmp == NULL)
	// 	return (sndry_alloc_err(NULL));
	// while (nums[idx] != '\0')
	// {
	// 	tmp[idx] = nums[idx];
	// 	idx++;
	// }
	// tmp[idx] = '\0';
	// return (tmp);
	return (nums);
}

char	*get_exit_no(void)
{
	char	*tmp;
	char	*exit_no;
	int		idx;
	int		len;

	idx = 0;
	exit_no = ft_itoa(g_ws);
	if (exit_no == NULL)
		return (memory_alloc_error());
	// len = ft_strlen(exit_no);
	// tmp = (char *)malloc(sizeof(char) * (len + 1));
	// if (tmp == NULL)
	// 	return (sndry_alloc_err(NULL));
	// while (exit_no[idx] != '\0')
	// {
	// 	tmp[idx] = exit_no[idx];
	// 	idx++;
	// }
	// tmp[idx] = '\0';
	// return (tmp);
	return (exit_no);
}
