FLAGS = -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit

NAMELIB = libft.a

NAME = CUBE3D.a

SRC = cub3d.c move.c utils.c cast.c

O = $(SRC:.c=.o)

all : $(NAME)

$(NAMELIB) :
	make -C libft/
	cp libft/$(NAMELIB) .

$(NAME) : $(NAMELIB)
	ar x $(NAMELIB)
	gcc $(FLAGS) -c $(SRC) $(MLX) $(FRAMEWORKS)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean :
	make clean -C libft/
	rm -f *.o

fclean : clean
	make fclean -C libft/
	rm -f *.a

re : fclean all
