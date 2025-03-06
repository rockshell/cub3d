NAME		:=	cub3d

CFLAGS		:=	-Wextra -Wall -Werror -g -O3 -Ofast -flto # check what these flags do
LDFLAGS		:=	-lreadline

HEADERS		:=	-I ./include -I $(LIBMLX)/include

LIBFT_DIR 	:=	./Libft
LIBFT		:=	./lib/libft.a

LIBMLXDIR	:=	./MLX42/
LIBMLX		:=	$(LIBMLXDIR)/build/libmlx42.a

LIBS		:=	$(LIBFT) $(LIBMLX) -ldl -lglfw -lm # -pthread

SRCS_DIR	:=	./src/
SRCS 		:=	main.c get_next_line.c parsing.c ft_isspace.c cleanup.c

SRCS		:=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS		:=	${SRCS:.c=.o}


all: $(LIBMLX) $(NAME)

libmlx:
	@cmake $(LIBMLXDIR) -B $(LIBMLXDIR)/build && make -C $(LIBMLXDIR)/build -j4

# $(LIBFT):
# 	@echo "Building libft..."
# 	@$(MAKE) -C $(LIBFT_DIR)

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
#	 @rm -rf $(LIBFT)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@echo "\nPerforming full clean..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
