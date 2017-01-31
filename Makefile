

### Project directory ###
LIB=./libft/libft.a
LIBFT_INCLUDE=./libft
SRCDIR=src
INCLUDE=include

### Compilator options ###
CC=gcc
CFLAGS=-Wall -Werror -Wextra
SRC=main.c\
tetriminos.c\
solver.c\
display.c\
solver2.c\
init_solver.c
NAME=fillit

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJ=$(patsubst %.c, %.o, $(SRCS))


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -o $(NAME) $(OBJ) $(LIB)
	@printf "[ + ] Fillit compiled.                                            \n"

$(OBJ): %.o : %.c
	@printf "[+] Current: $<\r"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT_INCLUDE) $(LDLFAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
