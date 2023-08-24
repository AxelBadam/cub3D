NAME = cub3d
SRC = main.c init.c util.c draw.c draw_util.c pars.c raycast.c rc_util.c move.c cast_horizontal_rays.c cast_vertical_rays.c
LIBFT = libft
OBJECT = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -ffast-math
RM = rm -f
OBJDIR = obj
SRCDIR = src

all: obj $(OBJDIR) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT)
	@make -s -C $(LIBFT)
	$(CC) $(OBJECT) -framework Cocoa -framework OpenGL -framework IOKit \
	MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(LIBFT)/libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	@make -s clean -C $(LIBFT)
	$(RM) $(OBJECT)

fclean: clean
	@make -s fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all