#	o-----------------o
#	|    VARIABLES    |
#	o-----------------o

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit #-fsanitize=address -g

#	o-----------------o
#	|    INCLUDES     |
#	o-----------------o

INC = inc
LIBFT_INC = libft/includes
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

#	o-----------------o
#	|     SOURCES     |
#	o-----------------o

SRC_FILES = draw.c			\
			draw1.c			\
			frame_refresh.c	\
			frame_refresh1.c\
			frame_refresh2.c\
			frame_refresh3.c\
			frame_refresh4.c\
			frame_refresh5.c\
			bounds.c		\
			raycast.c		\
			raycast1.c		\
			raycast2.c		\
			raycast3.c		\
			raw_utils.c 	\
			gen_utils.c		\
			key_events.c	\
			initialize.c	\
			initialize1.c	\
			initialize2.c	\
			initialize3.c	\
			initialize4.c	\
			init_player.c	\
			box_collider.c	\
			parse.c 		\
			parse1.c 		\
			parse2.c 		\
			parse3.c 		\
			parse4.c 		\
			parse5.c 		\
			parse6.c 		\
			parse7.c 		\
			parse8.c 		\
			parse9.c 		\
			parse10.c 		\
			main.c

SRC_DIR = src

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj

OBJ_RAW = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_RAW))

#	o-----------------o
#	|      RULES      |
#	o-----------------o

all: $(OBJ_DIR) $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -L libft -lft $(LFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Making $<"
	$(CC) $(CFLAGS) -I $(INC) -I $(LIBFT_INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	@echo "Making libft"
	$(MAKE) -C libft

$(MLX):
	@echo "Making mlx"
	$(MAKE) -C mlx

clean:
	$(MAKE) clean -C libft
	@make -C mlx clean
	rm -f $(OBJS)
	rm -df $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
