INCMYLIB=./lib/
INCCORE=./core/

NAME = pipex

SRC = main.c $(INCCORE)child.c  $(INCCORE)utils.c $(INCMYLIB)ft_strnstr.c $(INCMYLIB)ft_putchar_fd.c $(INCMYLIB)ft_putnbr_fd.c $(INCMYLIB)ft_putstr_fd.c $(INCMYLIB)ft_bzero.c $(INCMYLIB)ft_calloc.c $(INCMYLIB)ft_strlcpy.c $(INCMYLIB)ft_strlen.c $(INCMYLIB)ft_strdup.c $(INCMYLIB)ft_strlcat.c $(INCMYLIB)ft_strjoin.c $(INCMYLIB)ft_split.c

FLAG = -Wall -Werror -Wextra

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):	$(OBJ)
		gcc $(FLAG) -o $(NAME) $(OBJ)

clean:
	rm -rf *.o
	rm -rf $(INCMYLIB)*.o
	rm -rf $(INCCORE)*.o

fclean:
	rm -rf $(NAME)

re: clean all
