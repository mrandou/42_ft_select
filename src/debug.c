/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:10:27 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/07 16:22:20 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	debug_print_struct(t_select *slt_struct)
{
	ft_putendl("\n- FT_SELECT INFOS - \n");
	ft_putstr("fd -> ");
	ft_putnbr(slt_struct->fd);
	ft_putstr( " current -> ");
	ft_putnbr(slt_struct->current);
	ft_putstr( " max -> ");
	ft_putnbr(slt_struct->max);
	ft_putstr( " nb_delete -> ");
	ft_putnbr(slt_struct->nb_delete);
	ft_putstr( " max_len -> ");
	ft_putnbr(slt_struct->max_len);
	ft_putstr( " ws.col -> ");
	ft_putnbr(slt_struct->window.ws_col);
	ft_putstr( " ws_row -> ");
	ft_putnbr(slt_struct->window.ws_row);
	ft_putbn();
	ft_putendl("\n- LISTE - ");
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		ft_putstr(CLR_RED"\nCONTENT -> ");
		ft_putstr(CLR_GREEN"(");
		ft_putstr(slt_struct->arg_list->content);
		ft_putchar(')');
		ft_putstr(CLR_RED" ID -> ");
		ft_putstr(CLR_GREEN"(");
		ft_putnbr(slt_struct->arg_list->id);
		ft_putchar(')');
		ft_putstr(CLR_RED" SELECTED -> ");
		ft_putstr(CLR_GREEN"(");
		ft_putnbr(slt_struct->arg_list->selected);
		ft_putchar(')');
		ft_putstr(CLR_RED" DELETED -> ");
		ft_putstr(CLR_GREEN"(");
		ft_putnbr(slt_struct->arg_list->deleted);
		ft_putstr(")"TCA_OFF);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	ft_putendl("\n\n - RESULT - \n");
}
