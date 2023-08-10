NAME = cub3d
SRC = main.c
LIBFT = libft
OBJECT = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g
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
	MLX42/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" $(LIBFT)/libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	@make -s clean -C $(LIBFT)
	$(RM) $(OBJECT)

fclean: clean
	@make -s fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all