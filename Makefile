#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 16:06:58 by okryzhan          #+#    #+#              #
#    Updated: 2018/12/20 16:06:59 by okryzhan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

FLAGS = -Wall -Werror -Wextra
CC = gcc

SRCS = main.c \
print_col_row.c \
print_utils.c \
parse_dir.c \
parser.c \
utils.c \
sort_files.c \
tests.c

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

LIB_DIR = ./libft
LIB_NAME = ft
LIB = -L $(LIB_DIR) -l$(LIB_NAME)
LIB_HEAD = ./libft/includes
LIBFT = $(LIB_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIB) -I $(LIB_HEAD)

$(OBJS_DIR)/%.o: %.c $(OBJS_DIR) $(LIB_HEAD)/*.h *.h
	$(CC) -o $@ -c $< -I $(LIB_HEAD)

$(OBJS_DIR):
	@mkdir objs
	@echo "objs dir created" 

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "objs directory deleted"

fclean: clean
	@rm -rf $(NAME)
	@echo "executable deleted"

re: fclean all