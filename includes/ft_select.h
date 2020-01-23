/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:09:05 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/23 18:36:52 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SELECT_H
# define __FT_SELECT_H

# include "../libft/incs/libft.h"
# include <termios.h>

# define SUCCESS	0
# define FAILURE	1

int		ft_select(char **arg_list);

int		init_set_attribute(struct termios *backup);
int		init_reset_attribute(struct termios backup);

#endif
