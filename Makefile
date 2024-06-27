# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:44:39 by rukoltso          #+#    #+#              #
#    Updated: 2024/06/27 15:30:21 by rukoltso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinc

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[1;33m
NC = \033[0m

SRCDIR = src
SRC = $(shell find $(SRCDIR) -name '*.c')

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $@!$(NC)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) -lpthread
	@echo "$(YELLOW)Done!$(NC)"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning up! $(NC)"
	@rm -rf $(OBJ_DIR) > /dev/null

fclean: clean
	@echo "$(RED)Cleaning $(NAME)! $(NC)"
	@rm -f $(NAME) > /dev/null
	@echo "$(YELLOW)Done Cleaning!$(NC)"

re: fclean all

.PHONY: all clean fclean re