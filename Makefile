NAME = cub3D
SRC = main.c init.c util.c util_2.c draw.c draw_util.c map_parsing.c raycast.c move.c cast_horizontal_rays.c cast_vertical_rays.c \
parse_util.c parse_util2.c map_check.c map_check2.c get_int_map.c get_map_attr.c parse_util3.c move_2.c
LIBFT = libft
OBJECT = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -ffast-math
RM = rm -f
OBJDIR = obj
SRCDIR = src
GIT_REPO_URL = https://github.com/codam-coding-college/MLX42
CLONE_DIR = MLX42
GIT_REPO_EXISTS := $(shell if [ -d "$(CLONE_DIR)/.git" ]; then echo "1"; else echo "0"; fi)

all: clone obj $(OBJDIR) $(NAME)

clone:

ifeq ($(GIT_REPO_EXISTS),0)
	git clone $(GIT_REPO_URL) $(CLONE_DIR)
endif

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT)
	@make -s -C $(LIBFT)
	cmake -B build MLX42
	cmake --build build -j4
	$(CC) $(OBJECT) -framework Cocoa -framework OpenGL -framework IOKit \
	build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" $(LIBFT)/libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	rm -rf build
	@make -s clean -C $(LIBFT)
	$(RM) $(OBJECT)

fclean: clean
	@make -s fclean -C $(LIBFT)
	rm -rf build
	$(RM) $(NAME)
	rm -rf MLX42

re: fclean
	$(eval GIT_REPO_EXISTS = 0)
	@make -s all

