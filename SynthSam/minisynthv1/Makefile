NAME = minisynth

HEADER = includes

SOURCE_FOLDER = src/
FILES = minisynth playback

SOURCE_FILES = $(patsubst %, $(SOURCE_FOLDER)%.c, $(FILES))
OBJECT_FILES = $(patsubst %, %.o, $(FILES))

Flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(SOURCE_FILES)
			gcc -c $(FLAGS) $(SOURCE_FILES) -I $(HEADER)
			gcc $(FLAGS) $(OBJECT_FILES) -o $(NAME)
			make clean

clean:
			rm -f $(OBJECT_FILES)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re