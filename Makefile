NAME			= cub3D

OBJDIR			= obj/
INCDIR			= include/

SRCS			= src/main.c


OBJS			= $(SRCS:src/%.c=$(OBJDIR)%.o)

LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a

MINILIBX_DIR	= minilibx-linux/
MINILIBX		= minilibx-linux/libmlx.a

CC				= cc
INCLUDES		= -I $(INCDIR) -I $(LIBFT_DIR)/include -I $(MINILIBX_DIR)
CFLAGS			= -Wall -Wextra -Werror
LDFLAGS			= -L $(MINILIBX_DIR) -lmlx -lXext -lX11 -lm
RM				= rm -f

GREEN			= \033[1;38;5;76m
ROSEBUD			= \033[1;38;5;199m
RESET			= \033[0m

all:			$(LIBFT) $(MINILIBX) $(NAME)

$(NAME):		$(OBJS) $(LIBFT) $(MINILIBX)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME) $(LDFLAGS)

$(OBJDIR)%.o:	src/%.c $(INCDIR)cub3d.h
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
				@echo "$(GREEN)Compiling libft..."
				@make -sC $(LIBFT_DIR)
				@echo "Libft compiled!$(RESET)"

$(MINILIBX):
				@echo "$(ROSEBUD)Сompiling MiniLibX...$(RESET)"
				@make -sC $(MINILIBX_DIR)
				@echo "$(ROSEBUD)MiniLibX compiled!$(RESET)"

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				$(MAKE) -C $(MINILIBX_DIR) clean
				rm -rf $(OBJDIR)

fclean:			clean
				$(RM) $(NAME) $(LIBFT) $(MINILIBX)

re: 			fclean all

.PHONY: 		all clean fclean re