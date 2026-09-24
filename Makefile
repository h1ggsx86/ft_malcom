CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

NAME	= ft_malcom

LIBFT_DIR	= libft
OBJ_DIR		= obj
INC_DIR		= includes
SRC_DIR		= srcs

LIBFT_LIB	= libft/libft.a
SRC		= $(SRC_DIR)/main.c $(SRC_DIR)/check.c $(SRC_DIR)/utils.c $(SRC_DIR)/print.c
SRC_OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(SRC_OBJ)
		$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -o $@ $^ $(LIBFT_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -O3 -c $< -o $@

$(LIBFT_LIB):
		(make --no-print-directory -C $(LIBFT_DIR))

$(OBJ_DIR):
		mkdir -p $@

clean:
		@echo "[CLEAN]: "
		@if [ ! -d "$(OBJ_DIR)" ]; \
		then \
			echo "Repo '.o' already clean"; echo ; \
		else \
			rm -rfv $(OBJ_DIR); \
			echo ;\
		fi
		@echo "Cleaning libft..."
		@(make --no-print-directory -C $(LIBFT_DIR) fclean)
		@echo

fclean: clean
		@echo "[FCLEAN]: "
		@if [ -f "$(NAME)" ]; \
		then \
			rm -fv $(NAME); \
		else \
			echo "Executable already removed"; echo; \
		fi
		(make --no-print-directory -C $(LIBFT_DIR) fclean)

re: fclean all

.PHONY: all clean fclean re