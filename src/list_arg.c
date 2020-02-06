/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:48:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/06 13:08:32 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	list_create(t_select *slt_struct, char **arg)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	slt_struct->arg_list = NULL;
	slt_struct->max_len = 0;
	while (arg[i])
	{
		len = ft_strlen(arg[i]);
		if (len > 32)
			arg[i][29]='\0';
		if (list_push(&slt_struct->arg_list, arg[i]))
			return (FAILURE);
		if ((len = ft_strlen(arg[i])) > slt_struct->max_len)
			slt_struct->max_len = len;
		i++;
	}
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

int		list_id_position(t_select *slt_struct, int id)
{
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (slt_struct->arg_list->id == id)
			return (SUCCESS);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	return (FAILURE);
}
