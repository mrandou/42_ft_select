/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:46 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 17:02:30 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		exec_main(struct s_select *slt_struct, int action)
{
	if (action == ESCAPE)
		return (ESCAPE);
	// if (action == RIGHT || action == LEFT)
	// 	exec_lr_motion(slt_struct, action);
	if (action == RIGHT)
	{
		slt_struct->current++;
		if (slt_struct->current > slt_struct->max)
			slt_struct->current = 0;
	}
	if (action == LEFT)
	{
		slt_struct->current--;
		if (slt_struct->current < 0)
			slt_struct->current = slt_struct->max;
	}
	return (SUCCESS);
}

void	exec_lr_motion(t_select *slt_struct, int motion)
{
	(void)motion;
	(void)slt_struct;
	// if (motion == RIGHT)
	// {
	// 	if (slt_struct->arg_list->next)
	// 		slt_struct->arg_list = slt_struct->arg_list->next;
	// 	while (slt_struct->arg_list->deleted && slt_struct->arg_list)
	// 	{
	// 		slt_struct->arg_list = slt_struct->arg_list->next;
			
	// 	}

	// }
	// else
	// {
		
	// }
	
}
