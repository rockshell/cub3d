NAME		:=	cub3d

CFLAGS		:=	-Wextra -Wall -Werror -O3 -Ofast -flto # check what these flags do
LDFLAGS		:=	-lreadline

HEADERS		:=	-I include

LIBFT_DIR 	:=	./lib/Libft
LIBFT		:=	./lib/libft.a

LIBMLXDIR	:=	./lib/MLX42/
LIBMLX		:=	./lib/libmlx42.a

LIBS		:=	$(LIBFT) $(LIBMLX) -ldl -lglfw -lm

SRCS_DIR	:=	./src/
SRCS 		:=	main.c get_next_line.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS		:=	${SRCS:.c=.o}

all: $(LIBMLX) $(NAME)

# libmlx:
# 	@cmake $(LIBMLXDIR) -B $(LIBMLXDIR)/build && make -C $(LIBMLXDIR)/build -j4

$(LIBFT):
	@echo "Building libft..."
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
	@echo "\nPerforming full clean..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx
