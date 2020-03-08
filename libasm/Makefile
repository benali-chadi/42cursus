NAME = libasm.a

NA = nasm -f macho64

NFLAGS = 

SRC = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

OBJ = $(SRC:.s=.o)

all: $(NAME)

%.o: %.s
	$(NA) $^

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)
	rm -f ./exec

fclean: clean
	rm -f $(NAME)

re: fclean all


test: re
	rm -f $(B_OBJ)
	rm -f ./exec
	gcc -L. -lasm -o exec main.c
	./exec