NAME		:=	cub3d

CFLAGS		:=	-Wextra -Wall -Werror -g -Ofast #-flto # check what these flags do
LDFLAGS		:=	-lreadline

HEADERS		:=	-I ./include -I $(LIBMLX)/include

LIBFT_DIR 	:=	./Libft
LIBFT		:=	./lib/libft.a

LIBMLX		:=	 MLX42/build/libmlx42.a

LIBS		:=	$(LIBFT) $(LIBMLX) -ldl -lglfw -lm -lpthread

SRCS_DIR	:=	./src/
SRCS 		:=	main.c parsing.c cleanup.c utils.c error.c \
				rays.c render.c controls.c init.c player.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS		:=	${SRCS:.c=.o}


all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

$(LIBFT):
	@echo "Building libft..."
	@mkdir -p lib
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@echo "Compiling $< to $@..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
	@echo "Linking object files to create $(NAME)...\n"
	@echo "'$(NAME)' executable successfully created"

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing executables and static libraries..."
	@rm -f $(NAME)
	@rm -rf $(LIBFT)

mlx_clean:
	@echo "Cleaning MLX42 lib build files"
	@rm -rf MLX42/build

super_clean: fclean mlx_clean
	@echo "Absolute purge initiated!"

re: fclean all

.PHONY: all clean fclean re libmlx mlx_clean super_clean
