/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:24:30 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 17:58:30 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*get_struct(t_select *slt_struct)
{
	static t_select *data_struct;

	if (slt_struct)
		data_struct = slt_struct;
	else
		return (data_struct);
	return (NULL);
}

int			put_char(int c)
{
	if (!c)
		return (ERROR);
	ft_putchar_fd(c, 0);
	return (c);
}

int			put_termcap(char *str, int nb)
{
	char	*termc;
	int		i;

	i = 0;
	termc = tgetstr(str, NULL);
	if (!termc)
		return (FAILURE);
	while (i < nb)
	{
		if (tputs(termc, 1, put_char))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
