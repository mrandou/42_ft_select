/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:48:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 17:17:28 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	list_create(t_select *slt_struct, char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
		if (list_push(&slt_struct->arg_list, arg[i++]))
			return (FAILURE);
	slt_struct->max = slt_struct->arg_list->id;
	slt_struct->tail = slt_struct->arg_list;
	while (slt_struct->arg_list->prev)
		slt_struct->arg_list = slt_struct->arg_list->prev;
	slt_struct->head = slt_struct->arg_list;
	return (SUCCESS);
}

int	list_push(t_arglist **arglist, char *content)
{
	t_arglist *newlist;

	if (!(newlist = (t_arglist *)malloc(sizeof(t_arglist))))
		return (FAILURE);
	newlist->selected = 0;
	newlist->deleted = 0;
	newlist->id = 0;
	if (!(newlist->content = ft_strdup(content)))
	{
		if (newlist)
			free(newlist);
		return (FAILURE);
	}
	newlist->prev = *arglist;
	newlist->next = NULL;
	if (*arglist)
	{
		newlist->id = (*arglist)->id + 1;
		(*arglist)->next = newlist;
	}
	*arglist = newlist;
	return (SUCCESS);
}

void	list_free(t_arglist *arglist)
{
	t_arglist	*tmp;

	while (arglist->prev)
		arglist = arglist->prev;
	while (arglist)
	{
		tmp = arglist->next;
		if (arglist->content)
			free(arglist->content);
		if (arglist)
			free(arglist);
		arglist = tmp;
	}
}

void	list_set_current_pos(t_select *slt_struct)
{
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (slt_struct->arg_list->id == slt_struct->current)
			return ;
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
}
