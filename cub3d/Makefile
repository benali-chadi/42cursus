FLAGS = -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit

NAMELIB = libft.a

NAME = CUBE3D.a

EXEC = run

SRC = cast.c cub3d.c draw.c move.c read_file.c render_3d.c render_spt.c utils2.c utils3.c

O = $(SRC:.c=.o)

all : $(NAME)

$(NAMELIB) :
	make -C libft/
	cp libft/$(NAMELIB) .

$(NAME) : $(NAMELIB)
	gcc $(FLAGS) $(SRC) -g3 -I /usr/local/include libft.a gnl/get_next_line.c gnl/get_next_line_utils.c -L /usr/local/lib -lmlx -framework OpenGl -framework Appkit -D BUFFER_SIZE=20 -o $(EXEC)

clean :
	make clean -C libft/
	rm -f *.o

fclean : clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(EXEC)

re : fclean all
