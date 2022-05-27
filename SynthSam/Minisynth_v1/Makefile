NAME = minisynth

HEADER = include

SOURCE_FOLDER = src/
FILES = minisynth playback wavfile write_pcm simple_mixing

SOURCE_FILES = $(patsubst %, $(SOURCE_FOLDER)%.c, $(FILES))
OBJECT_FILES = $(patsubst %, %.o, $(FILES))

ADD_LIBFT = -L libft/ -lft

Flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(SOURCE_FILES)
			make -C libft/ all
			gcc $(FLAGS) $(SOURCE_FILES) $(ADD_LIBFT) -o $(NAME)

clean:
			make -C libft/ clean
			rm -f $(OBJECT_FILES)

fclean:		clean
			rm -f $(NAME)
			make -C libft/ fclean

re:			fclean all

.PHONY: all clean fclean re