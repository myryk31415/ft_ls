# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 15:34:56 by padam             #+#    #+#              #
#    Updated: 2024/08/09 23:25:44 by padam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = cc
CFLAGS =  $(INCLUDES) -Wall -Wextra -Werror
INCLUDES = -I./includes
LIBS = -lreadline
LIBFT_DIR = libft

SRC_PATH = src
OBJ_PATH = obj

OBJ_DIRS =

SRCS_MAIN =	main.c parser.c

SRC_NAME =										$(SRCS_MAIN)	\
#			$(addprefix ,							$())		\

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): ascii_art $(LIBFT_DIR)/libft.a $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(LIBS) $(OBJS) $(LIBFT_DIR)/libft.a
	@printf "$(GREEN)%-100s\n\n$(RESET)" "$(NAME) compiled"

$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

$(OBJ_PATH)	:
	@mkdir -p $(OBJ_PATH)
ifneq ($(OBJ_DIRS),)
	@mkdir -p $(addprefix $(OBJ_PATH)/,$(OBJ_DIRS))
endif

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@printf "%-100s\r" "$(CC) $(CFLAGS) -o $@"
	@$(CC) $(CFLAGS) -o $@ -c $<

init_submodules:
	git submodule update --init --recursive

update_submodules:
	git submodule update --recursive --remote

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

ascii_art:
	@printf "$(RED)																						\n\
																										\n\
 .----------------.  .----------------.  .----------------.  .----------------.  .----------------.		\n\
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |	\n\
| |  _________   | || |  _________   | || |              | || |   _____      | || |    _______   | |	\n\
| | |_   ___  |  | || | |  _   _  |  | || |              | || |  |_   _|     | || |   /  ___  |  | |	\n\
| |   | |_  \_|  | || | |_/ | | \_|  | || |              | || |    | |       | || |  |  (__ \_|  | |	\n\
| |   |  _|      | || |     | |      | || |              | || |    | |   _   | || |   '.___\`-.   | |	\n\
| |  _| |_       | || |    _| |_     | || |              | || |   _| |__/ |  | || |  |\`\____) |  | |	\n\
| | |_____|      | || |   |_____|    | || |   _______    | || |  |________|  | || |  |_______.'  | |	\n\
| |              | || |              | || |  |_______|   | || |              | || |              | |	\n\
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |	\n\
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------'		\n\
																										\n\
                                                                                                 		\n\
                                                                         $(BLUE)by: padam$(RESET)		\n\
                                                                                                 		\n"

.PHONY: all, $(NAME), $(LIBFT_DIR)/libft.a, $(OBJ_PATH), $(OBJ_PATH), clean, fclean, re
