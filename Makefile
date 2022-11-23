# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 15:31:50 by pandalaf          #+#    #+#              #
#    Updated: 2022/11/23 17:57:48 by pandalaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target output
NAME := minishell
# Compiler options
CC := cc
CFLAGS := -Wall -Werror -Wextra
COPT := 
# Sources to compile
SRC_DIR := src/
SRC_FILES := main.c error.c parser.c validator.c memory.c commands.c init.c
SRC_RL_FILES := signals.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
SRCS_RL = $(addprefix $(SRC_DIR), $(SRC_RL_FILES))
# Libraries to compile (if using 42WOB computer, apply fix)
SYSLIB := -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
SYSLIB_OBJ := -I $(HOME)/goinfre/.brew/opt/readline/include/
LIBFT := libft.a
LIBFT_PATH := libft/
LIBFT_FULL = $(addprefix $(LIBFT_PATH), $(LIBFT))
# Objects to compile
OBJ_DIR := obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
OBJS_RL = $(addprefix $(OBJ_DIR), $(SRC_RL_FILES:.c=.o))

# Make desired target
all: directories $(NAME)

# Make the target executable
$(NAME): $(OBJS) $(OBJS_RL) $(LIBFT_FULL)
	$(CC) $(CFLAGS) $(COPT) -o $(NAME) $^ $(LIBFT_FULL) $(SYSLIB)

# Make required directories
directories: $(OBJ_DIR)

# Make object files that require linker
$(addprefix $(OBJ_DIR), $(SRC_RL_FILES:.c=.o)): $(SRCS_RL) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^ $(SYSLIB_OBJ)

# Make object files
$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

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
