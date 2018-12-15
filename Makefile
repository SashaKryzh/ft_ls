
NAME = ft_ls

FLAGS = -Wall -Werror -Wextra
CC = gcc

SRCS = main.c

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