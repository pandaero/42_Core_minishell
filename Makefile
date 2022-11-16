# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_old                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 15:31:50 by pandalaf          #+#    #+#              #
#    Updated: 2022/11/16 22:52:30 by pandalaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target output
NAME := minishell
# Compiler options
CC := cc
CFLAGS := -Wall -Werror -Wextra
COPT := -g
# Sources to compile
SRC_DIR := src/
SRC_FILES := main.c execute.c error.c parser.c list.c memory.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
# Libraries to compile
SYSLIB := -lreadline
LIBFT := libft.a
LIBFT_PATH := libft/
LIBFT_FULL = $(addprefix $(LIBFT_PATH), $(LIBFT))
# Objects to compile
OBJ_DIR := obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Make desired target
all: directories $(NAME)

# Make the target executable
$(NAME): $(OBJS) $(LIBFT_FULL)
	$(CC) $(CFLAGS) $(SYSLIB) $(COPT) -o $(NAME) $^ $(LIBFT_FULL)

# Make required directories
directories: $(OBJ_DIR)

# Make object files
$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SYSLIB) -c -o $@ $^

# Make library archive
$(LIBFT_FULL): $(LIBFT_PATH)
	make -C libft/ bonus

# Make object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean intermediate files
clean:
	make -C libft/ clean
	rm -rf $(OBJ_DIR)

# Clean all non-source files
fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

# Clean everything and recompile
re: fclean all

# Make sure these aren't treated as files
.PHONY: all directories clean fclean re
