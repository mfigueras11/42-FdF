NAME = fdf
FILES = fdf fdf2 fdf3
OBJ_DIR = objs
SRCS_DIR = srcs
INCL_DIR = incl
OFILES = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
INCLUDES = incl/fdf.h
LIBRARY = libft/libft.a
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBRARY) $(OFILES)
	@gcc $(FLAGS) -o $(NAME) $(OFILES) -lmlx -framework OpenGL -framework AppKit $(LIBRARY)
	@echo "\033[0;32m[SUCCESS]"

$(LIBRARY):
	@make -C libft re

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	@gcc $(FLAGS) -c $< -o $@ -I $(INCL_DIR)

clean:
	@make -C libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean $(NAME)
