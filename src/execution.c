/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:52:46 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/03 15:59:05 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		exec_main(struct s_select *slt_struct, int action)
{
	if (action == RETURN)
		return (RETURN);
	if (action == ESCAPE)
		return (ESCAPE);
	if (action == DOWN)
		exec_motion_down(slt_struct);
	if (action == UP)
		exec_motion_up(slt_struct);
	if (action == RIGHT)
		exec_motion_right(slt_struct);
	if (action == LEFT)
		exec_motion_left(slt_struct);
	if (action == SPACE)
	{
		slt_struct->arg_list->selected = !slt_struct->arg_list->selected;
		exec_motion_down(slt_struct);
	}
	if (action == DEL || action == BACKSPACE)
		return (exec_delete(slt_struct));
	return (SUCCESS);
}

void	exec_motion_right(t_select *slt_struct)
{
	int	new;

	new = slt_struct->current + slt_struct->window.ws_row;
	if (!list_id_position(slt_struct, new))
		slt_struct->current = slt_struct->arg_list->id;
	else
	{
		slt_struct->arg_list = slt_struct->head;
		slt_struct->current = slt_struct->arg_list->id;
	}
}
void	exec_motion_left(t_select *slt_struct)
{
	int	new;

	new = slt_struct->current - slt_struct->window.ws_row;
	if (!list_id_position(slt_struct, new))
		slt_struct->current = slt_struct->arg_list->id;
	else
	{
		slt_struct->arg_list = slt_struct->tail;
		slt_struct->current = slt_struct->arg_list->id;
	}
}

void	exec_motion_down(t_select *slt_struct)
{
	if (slt_struct->arg_list->next)
		slt_struct->arg_list = slt_struct->arg_list->next;
	else
		slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list->deleted && slt_struct->arg_list)
	{
		if (!slt_struct->arg_list->next)
			slt_struct->arg_list = slt_struct->head;
		else
			slt_struct->arg_list = slt_struct->arg_list->next;
		if (slt_struct->arg_list->id == slt_struct->current)
			return ;
	}
	slt_struct->current = slt_struct->arg_list->id;
}

void	exec_motion_up(t_select *slt_struct)
{
	if (slt_struct->arg_list->prev)
		slt_struct->arg_list = slt_struct->arg_list->prev;
	else
		slt_struct->arg_list = slt_struct->tail;
	while (slt_struct->arg_list->deleted && slt_struct->arg_list)
	{
		if (!slt_struct->arg_list->prev)
			slt_struct->arg_list = slt_struct->tail;
		else
			slt_struct->arg_list = slt_struct->arg_list->prev;
		if (slt_struct->arg_list->id == slt_struct->current)
			return ;
	}
	slt_struct->current = slt_struct->arg_list->id;
}

int		exec_delete(t_select *slt_struct)
{
	t_arglist	*tmp;

	if (slt_struct->arg_list->id == (slt_struct->max - slt_struct->nb_delete))
		slt_struct->current--;
	slt_struct->arg_list->deleted = 1;
	slt_struct->arg_list->id = -1;
	slt_struct->nb_delete++;
	if (slt_struct->nb_delete > slt_struct->max)
		return (ESCAPE);
	tmp = slt_struct->arg_list;
	while (slt_struct->arg_list)
	{
		slt_struct->arg_list->id--;
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	slt_struct->arg_list = tmp;
	return (SUCCESS);
}
