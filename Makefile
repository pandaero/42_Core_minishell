# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 15:31:50 by pandalaf          #+#    #+#              #
#    Updated: 2022/12/14 18:20:41 by zyunusov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target output
NAME := minishell
# Compiler options
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra 
COPT	:= -g
# Sources
SRC_ROOT		:= src/
SRC_SUBDIRS		:= main builtin lexer parser error list memory validation utils executor
SRC_RL_FILES	:= main/main.c signal/signals.c	builtin/builtin_exit.c		
SRCS_RL			:= $(addprefix $(SRC_ROOT), $(SRC_RL_FILES))
SRC_DIR			:= $(addprefix $(SRC_ROOT), $(SRC_SUBDIRS))
SRCS			:= $(foreach subdir, $(SRC_DIR), $(wildcard $(subdir)/*.c))
# Libraries to compile (if using 42WOB computer, apply fix)
SYSLIB		:= -I $(HOME)/goinfre/.brew/opt/readline/include/ \
				-L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
SYSLIB_OBJ	:= -I $(HOME)/goinfre/.brew/opt/readline/include/
# Libft library
LIBFT		:= libft.a
LIBFT_PATH	:= libft/
LIBFT_FULL	:= $(addprefix $(LIBFT_PATH), $(LIBFT))
# Objects to compile
OBJ_DIR	:= build/
OBJS_RL	:= $(addprefix $(OBJ_DIR), $(notdir $(SRC_RL_FILES:.c=.o)))
OBJS	:= $(patsubst %.c, %.o, $(notdir $(SRCS)))
OBJS	:= $(addprefix $(OBJ_DIR), $(OBJS))

# Look for (.c) files in the following directories if not found elsewhere
vpath %.c $(SRC_DIR)

# Make desired target
all: directories $(NAME)

ifeq ($(shell uname -s), Linux)
SYSLIB := -lreadline
SYSLIB_OBJ := -lreadline
endif

# Make the target executable
$(NAME): $(OBJS) $(OBJS_RL) $(LIBFT_FULL)
	$(CC) $(CFLAGS) $(COPT) $< $(filter-out $<, $^) -o $@ $(LIBFT_FULL) \
	$(SYSLIB)

# Make required directories
directories: $(OBJ_DIR)

# Make object files that require linker
$(word 1, $(OBJS_RL)): $(word 1, $(SRCS_RL)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ $(SYSLIB_OBJ)
$(word 2, $(OBJS_RL)): $(word 2, $(SRCS_RL)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ $(SYSLIB_OBJ)
$(word 3, $(OBJS_RL)): $(word 3, $(SRCS_RL)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ $(SYSLIB_OBJ)

# Make object files
$(addprefix $(OBJ_DIR), %.o): %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

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
