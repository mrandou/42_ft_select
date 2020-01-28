/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:46 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 17:50:43 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		exec_main(struct s_select *slt_struct, int action)
{
	if (action == ESCAPE)
		return (ESCAPE);
	if (action == RIGHT)
		exec_motion_right(slt_struct);
	if (action == LEFT)
		exec_motion_left(slt_struct);
	if (action == SPACE)
		slt_struct->arg_list->selected = !slt_struct->arg_list->selected;
	if (action == DEL || action == BACKSPACE)
	{
		slt_struct->arg_list->deleted = 1;
		slt_struct->nb_delete++;
		if (slt_struct->nb_delete == slt_struct->max + 1)
			return (ESCAPE);
		exec_motion_right(slt_struct);
	}
	return (SUCCESS);
}

void	exec_motion_right(t_select *slt_struct)
{
	if (slt_struct->arg_list->next)
		slt_struct->arg_list = slt_struct->arg_list->next;
	else
		slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list->deleted && slt_struct->arg_list)
	{
		slt_struct->arg_list = slt_struct->arg_list->next;
		if (!slt_struct->arg_list->next)
			slt_struct->arg_list = slt_struct->head;
		if (slt_struct->arg_list->id == slt_struct->current)
			return ;
	}
	slt_struct->current = slt_struct->arg_list->id;
}

void	exec_motion_left(t_select *slt_struct)
{
	if (slt_struct->arg_list->prev)
		slt_struct->arg_list = slt_struct->arg_list->prev;
	else
		slt_struct->arg_list = slt_struct->tail;
	while (slt_struct->arg_list->deleted && slt_struct->arg_list)
	{
		slt_struct->arg_list = slt_struct->arg_list->prev;
		if (!slt_struct->arg_list->prev)
			slt_struct->arg_list = slt_struct->tail;
		if (slt_struct->arg_list->id == slt_struct->current)
			return ;
	}
	slt_struct->current = slt_struct->arg_list->id;
}
