# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 12:48:20 by aurban            #+#    #+#              #
#    Updated: 2023/12/05 16:10:39 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -I$(INCLUDE_PATH) -g3 -fsanitize=address
RM:=rm -rf

NAME:=pipex

SRC_PATH:=./src
LIBFT_PATH:=./libft

SRC_FILES:=main.c parser.c utils.c pipex.c pipex_io_files.c pipex_group_chat.c pipex_stream.c
BONUS_FILES:=bonus/main_bonus.c bonus/parser_bonus.c utils.c bonus/pipex_bonus.c pipex_io_files.c pipex_group_chat.c pipex_stream.c

SRC_FILES:= $(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC_FILES))

BONUS_FILES:= $(addprefix $(SRC_PATH)/,$(BONUS_FILES))
BONUS_OBJECTS:= $(patsubst %.c,%.o,$(BONUS_FILES))

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS) -o $@

bonus: $(BONUS_OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS) -o $(NAME)_bonus

both: all bonus

clean:
	@make -C $(LIBFT_PATH)/ clean
	@$(RM) $(SRC_OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@$(RM) $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re libft pipex