CC = clang
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
SRC = main.c \
	  get_next_line.c \
	  get_next_line_utils.c

OBJ_DIR = src/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

HEADER_FILES = incl/get_next_line.h

NAME = CommentMyCCode

VPATH = src

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@
	  	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
