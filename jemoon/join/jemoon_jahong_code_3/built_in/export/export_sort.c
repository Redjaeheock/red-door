/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:36:10 by jemoon            #+#    #+#             */
/*   Updated: 2025/02/07 09:50:56 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../syntax/syntax.h"
#include "../built_in.h"

void	swap_first_two(t_path **exp)
{
	t_path	*temp_head;
	t_path	*two_head;
	t_path	*last_head;

	if (ft_lstsize(*exp) <= 1)
		return ;
	temp_head = *exp;
	two_head = temp_head->next;
	if (two_head != NULL)
	{
		last_head = two_head->next;
		two_head->next = temp_head;
		temp_head->next = last_head;
		*exp = two_head;
	}
}

void	swap_middle_two(t_path *exp_prev)
{
	t_path	*temp_head;
	t_path	*two_head;
	t_path	*last_head;

	if (exp_prev == NULL || exp_prev->next == NULL || \
		exp_prev->next->next == NULL)
		return ;
	temp_head = exp_prev->next;
	two_head = temp_head->next;
	last_head = two_head->next;
	exp_prev->next = two_head;
	two_head->next = temp_head;
	temp_head->next = last_head;
}

void	swap_export(t_path **exp, t_path *exp_prev)
{
	if (exp_prev == NULL)
		swap_first_two(exp);
	else
		swap_middle_two(exp_prev);
}

void	bubble_sort(t_path **exp, int *swapped)
{
	t_path	*tmp_i;
	t_path	*tmp_j;
	t_path	*tmp_i_prev;

	tmp_i = *exp;
	tmp_i_prev = NULL;
	while (tmp_i && tmp_i->next)
	{
		tmp_j = tmp_i->next;
		if (ft_test(tmp_i->key, tmp_j->key) > 0)
		{
			swap_export(&tmp_i, tmp_i_prev);
			*swapped = 1;
			if (tmp_i_prev == NULL)
				*exp = tmp_j;
		}
		tmp_i_prev = tmp_i;
		tmp_i = tmp_i->next;
	}
}

void	sort_export(t_path **exp)
{
	int	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		bubble_sort(exp, &swapped);
	}
}

/*
void	sort_export(t_path **exp)
{
	t_path	*tmp_i;
	t_path	*tmp_j;
	t_path	*tmp_i_prev;
	int		swapped;

	if (exp == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		tmp_i = *exp;
		tmp_i_prev = NULL;
		while (tmp_i && tmp_i->next)
		{
			tmp_j = tmp_i->next;
			if (ft_test(tmp_i->key, tmp_j->key) > 0)
			{
				swap_export(&tmp_i, tmp_i_prev);
				swapped = 1;
				if (tmp_i_prev == NULL)
					*exp = tmp_j;
			}
			tmp_i_prev = tmp_i;
			tmp_i = tmp_i->next;
		}
	}
}


void	swap_export(t_path **exp, t_path *exp_prev)
{
	t_path	*temp_head;
	t_path	*two_head;
	t_path	*last_head;

	if (ft_lstsize(*exp) <= 1)
		return ;
	if (exp_prev == NULL)
	{
		temp_head = *exp;
		two_head = temp_head->next;
		if (two_head != NULL)
		{
			last_head = two_head->next;
			two_head->next = temp_head;
			temp_head->next = last_head;
			*exp = two_head;
		}
	}
	else
	{
		temp_head = *exp;
		if (temp_head == NULL)
			return ;
		two_head = temp_head->next;
		if (two_head != NULL)
		{
			last_head = two_head->next;
			exp_prev->next = two_head;
			two_head->next = temp_head;
			temp_head->next = last_head;
		}
	}
}
*/