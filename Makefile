#	o-----------------o
#	|    VARIABLES    |
#	o-----------------o

NAME = cub3D
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
			gen_utils.c		\
			init_player.c	\
			initialize.c	\
			initialize1.c	\
			initialize2.c	\
			initialize3.c	\
			initialize4.c	\
			key_events.c	\
			main.c			\
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
			raw_utils.c 	\
			raycast.c		\
			raycast1.c		\
			raycast2.c		\

BONUS	=	box_collider_bonus.c	\
			draw.c					\
			draw1.c					\
			frame_refresh_bonus.c	\
			frame_refresh1_bonus.c	\
			frame_refresh2_bonus.c	\
			frame_refresh3_bonus.c	\
			frame_refresh4_bonus.c	\
			frame_refresh5_bonus.c	\
			gen_utils.c				\
			init_player.c			\
			initialize_bonus.c		\
			initialize1_bonus.c		\
			initialize2_bonus.c		\
			initialize3_bonus.c		\
			initialize4_bonus.c		\
			key_events.c			\
			main_bonus.c			\
			parse.c 				\
			parse1.c 				\
			parse2.c 				\
			parse3.c 				\
			parse4.c 				\
			parse5.c 				\
			parse6_bonus.c 			\
			parse7.c 				\
			parse8_bonus.c 			\
			parse9.c 				\
			parse10.c 				\
			raw_utils.c 			\
			raycast_bonus.c			\
			raycast1_bonus.c		\
			raycast2_bonus.c		\
			raycast3_bonus.c		\




SRC_DIR = src

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

BONUS_SRCS = $(addprefix $(SRC_DIR)/, $(BONUS))

OBJ_DIR = obj

OBJ_RAW = $(SRC_FILES:.c=.o)

BONUS_OBJ_RAW =  $(BONUS:.c=.o)

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_RAW))

BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_OBJ_RAW))

#	o-----------------o
#	|      RULES      |
#	o-----------------o

all: $(OBJ_DIR) $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -L libft -lft $(LFLAGS) -o $@

bonus: $(OBJ_DIR) $(LIBFT) $(MLX) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) -L libft -lft $(LFLAGS) -o $(NAME)

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
	rm -f $(BONUS_OBJS)
	rm -df $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re bonus
