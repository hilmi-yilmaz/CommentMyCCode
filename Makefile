CC = clang
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SRC_DIR = src/
SRC = main.c \
	  init.c \
	  comment.c \
	  parse_arguments.c \
	  parse_function_name.c \
	  parse_return.c \
	  utils.c \
	  terminate.c

OBJ_DIR = src/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

HEADER_FILES = incl/commentmyccode.h

LIBFT = libft.a
LIBFT_DIR = src/libft

NAME = CommentMyCCode

VPATH = src

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	  	
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
