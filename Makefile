UNAME := $(shell uname)

NAME = fdf
SRCS_DIR = srcs/
SRC_FILES = main.c hooks.c draw_grid.c fdf_bresenham.c read_map.c \
			init_map.c fdf_exit_prog.c fdf_utils.c color.c \
			bresenham_init_utils.c modify_image.c hooks_utils.c
SRCS = $(addprefix $(SRCS_DIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes
HEADER = includes/*
LINUX_MLX = minilibx-linux
LINUX_MLX_SRC = https://github.com/42Paris/minilibx-linux.git
MAC_MLX = minilibx_mms
MAC_MLX_SRC = https://projects.intra.42.fr/uploads/document/document/3774/minilibx_macos_sierra_20161017.tgz
MAC_MLX_TARZIP = minilibx_macos_sierra_20161017.tgz
MAC_MLX_TAR = minilibx_macos

ifeq ($(UNAME), Linux)
LIBS = ./libraries/libft/libft.a ./libraries/minilibx-linux/libmlx_Linux.a
USR_LIBS = -L/usr/lib -lXext -lm -lX11
all: linux_mlx $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C libraries/libft
	make -C libraries/minilibx-linux
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

clean:
	rm -f $(OBJS)
	make clean -C libraries/libft
	make clean -C libraries/$(LINUX_MLX)

else
LIBS = ./libraries/libft/libft.a ./libraries/minilibx_mms/libmlx.a
USR_LIBS = -framework OpenGL -framework AppKit
all: linux_mlx mac_mlx $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C libraries/libft
	make -C libraries/$(MAC_MLX)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

mac_mlx:
	@if [ ! -d libraries/"$(MAC_MLX)" ]; then \
		curl -O $(MAC_MLX_SRC); \
		tar -xzvf $(MAC_MLX_TARZIP); \
		rm $(MAC_MLX_TARZIP); \
		mv $(MAC_MLX_TAR) $(MAC_MLX); \
		mv $(MAC_MLX) libraries; \
	fi; \

clean:
	rm -f $(OBJS)
	make clean -C libraries/libft
	make clean -C libraries/$(MAC_MLX)

endif

linux_mlx:
	@if [ ! -d libraries/"$(LINUX_MLX)" ]; then \
		git clone $(LINUX_MLX_SRC) libraries/$(LINUX_MLX); \
	fi; \

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re linux_mlx mac_mlx
