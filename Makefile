# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 13:35:24 by mrandou           #+#    #+#              #
#    Updated: 2020/01/23 18:15:57 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = ft_select
LIBFT = ./libft/
LIBNAME = ./libft/libft.a

INC_DIR			=	./includes/
INC_NAME		=	ft_select.h

INC				=	$(addprefix $(INC_DIR), $(INC_NAME))

INC_DEPEND		= 	$(INC)

FILES			=	ft_select.c init_set_attribute.c\

SRC_PATH		= ./src/

FILES_SRC = $(addprefix $(SRC_PATH), $(FILES))

OBJ				= ./obj/
FILES_OBJ = $(addprefix $(OBJ), $(FILES:.c=.o))

CPPFLAGS		= -Iincludes
LDFLAGS			= -Llibft
LDLIBS			= -lft
CC				= gcc
CFLAGS			= -Werror -Wextra -Wall
TFLAGS			= -ltermcap
MAKEFILE		= ./Makefile

all:	compile

$(OBJ):
	@mkdir -p $@

$(OBJ)%.o: $(SRC_PATH)%.c $(INC_DEPEND)
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)
	@printf "ft_select --> \033[32m"
	@printf $<
	@printf "\r\033[0m\n\033[K\033[A\033[K"

$(NAME): $(MAKEFILE) $(OBJ) $(FILES_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $(FILES_OBJ) $(LIBNAME) $(TFLAGS)

compile:
	@printf "\033[1m\033[32m\n> ft_select Make <\n\n\033[0m"
	@make -C $(LIBFT)
	@make $(NAME)
	@printf "\n\033[K\033[A\033[K"
	@printf "ft_select Build \033[32mDone ✓\033[0m"
	@printf "\r\n\nBuild\033[32m Finish 🚀\\033[0m\n"
	
clean:
	@printf "\033[1m\033[31m\n> ft_select Make Clean <\n\n\033[0m"
	@rm -rf	$(OBJ)
	@rmdir	$(OBJ) 2> /dev/null || true
	@make -C $(LIBFT) clean
	@printf "All ---> \033[31mclean Done ✓\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)
	@printf "All ---> \033[31mfclean Done ✓\n\033[0m"

re: fclean all
