/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:44:52 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 16:42:48 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	exit_shutdown(int error)
{
	t_select *tmp;

	tmp = get_struct(NULL);
	if (tmp)
	{
		exit_list_free(tmp->arg_list);
		if (error != ER_NOTERM)
			if (exit_reset_attribute(tmp))
				exit(ER_RESET);
	}
	else
		exit(exit_check_error(ER_LIST));
	exit(exit_check_error(error));
}

int		exit_reset_attribute(t_select *slt_struct)
{
	ft_putstr_fd(CUR_ON, slt_struct->fd);
	ft_putstr_fd(ALTSCREEN_OFF, slt_struct->fd);
	close(slt_struct->fd);
	if (tcsetattr(STDIN_FILENO, 0, &slt_struct->backup))
		return (FAILURE);
	return (SUCCESS);
}

int		exit_check_error(int value)
{
	if (value == ER_READ)
		ft_putendl_fd("ft_select: READ Error", 2);
	else if (value == ER_EXEC)
		ft_putendl_fd("ft_select: EXECUTION Error", 2);
	else if (value == ER_INIT)
		ft_putendl_fd("ft_select: INITIALIZATION Error", 2);
	else if (value == ER_RESET)
		ft_putendl_fd("ft_select: RESET Error", 2);
	else if (value == ER_NOTERM)
		ft_putendl_fd("ft_select: Fail to load TERM configuration", 2);
	else if (value == ER_LIST)
		ft_putendl_fd("ft_select: FATAL ERROR", 2);
	else if (value == ER_WINDOW)
		ft_putendl_fd("ft_select: WINDOW ERROR", 2);
	else if (value == ESCAPE)
		return (SUCCESS);
	return (value);
}

void	exit_list_free(t_arglist *arglist)
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
