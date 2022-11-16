# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 18:00:54 by pandalaf          #+#    #+#              #
#    Updated: 2022/11/16 18:13:50 by pandalaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIBFT_FULL := libft/libft.a
SRCS := main.c error.c parser.c signals.c validator.c
SRCS_FULL = $(addprefix src/, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT_FULL) $(SRCS_FULL)
	cc -Wall -Werror -Wextra -lreadline -o $(NAME) $(SRCS_FULL) $(LIBFT_FULL)