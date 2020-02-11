/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:48:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/11 10:33:15 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		list_create(t_select *slt_struct, char **arg)
{
	int	i;
	int	len;

	i = 1;
	len = 0;
	slt_struct->arg_list = NULL;
	slt_struct->max_len = 0;
	slt_struct->colors = 1;
	slt_struct->win_small = 0;
	while (arg[i])
	{
		if (list_push(&slt_struct->arg_list, arg[i]))
			return (FAILURE);
		if ((len = ft_strlen(arg[i])) > slt_struct->max_len)
			slt_struct->max_len = len;
		if (len > 32)
			slt_struct->max_len = 32;
		i++;
	}
	slt_struct->max = slt_struct->arg_list->id;
	slt_struct->tail = slt_struct->arg_list;
	while (slt_struct->arg_list->prev)
		slt_struct->arg_list = slt_struct->arg_list->prev;
	slt_struct->head = slt_struct->arg_list;
	return (SUCCESS);
}

int		list_push(t_arglist **arglist, char *content)
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
	newlist->type = list_check_type(content);
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

int		list_head_tail(t_select *slt_struct, int direction)
{
	if (direction == HEAD || direction == HOME)
	{
		slt_struct->arg_list = slt_struct->head;
		while (slt_struct->arg_list && slt_struct->arg_list->deleted)
			slt_struct->arg_list = slt_struct->arg_list->next;
		slt_struct->current = slt_struct->arg_list->id;
		return (SUCCESS);
	}
	else
	{
		slt_struct->arg_list = slt_struct->tail;
		while (slt_struct->arg_list && slt_struct->arg_list->deleted)
			slt_struct->arg_list = slt_struct->arg_list->prev;
		slt_struct->current = slt_struct->arg_list->id;
		return (SUCCESS);
	}
	return (FAILURE);
}

int		list_id_position(t_select *slt_struct, int id)
{
	if (id < 0)
		return (FAILURE);
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (slt_struct->arg_list->id == id)
			return (SUCCESS);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	return (FAILURE);
}

int		list_check_type(char *arg)
{
	char			*path;
	char			*tmp;
	struct stat		infos;

	if (lstat(arg, &infos) == SUCCESS)
		return (infos.st_mode);
	if ((tmp = getenv("PWD")) == NULL)
		return (ERROR);
	if ((path = ft_strmjoin(tmp, "/", arg)) == NULL)
		return (ERROR);
	if (lstat(path, &infos) == -1)
	{
		ft_strdel(&path);
		return (ERROR);
	}
	ft_strdel(&path);
	return (infos.st_mode);
}
