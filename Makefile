CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft/includes -Iincludes
DFLAGS = $(CFLAGS) -g3

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a

SRC_DIR = src
SRC_FILES =	args_creators.c \
			ast_cleaner.c \
			builtins.c \
			builtins2.c \
			builtins_utils.c \
			command_line_error.c \
			env.c \
			env_utils.c \
			exec.c \
			exec_cmd_utils.c \
			exec_path.c \
			exec_redirection.c \
			free_all.c \
			here_doc.c \
			is_char_type.c \
			is_token_type.c \
			left_parser.c \
			lexemes_creators.c \
			lexer.c \
			main.c \
			main_walter.c \
			node_creators.c \
			parser.c \
			parsing_redirections.c \
			print_ast.c \
			quote_mask_maker.c \
			right_parser.c \
			runtime_cleaners.c \
			token_cleaners.c \
			token_creators.c \
			tree_traverse.c \
			tree_traverse_utils.c \
			utils.c \
			wildcards_2try.c \
			wildcards_matching.c \
			words.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

NAME = minishell

all: $(LIB_NAME) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

debug: fclean
	$(MAKE) -C $(LIB_DIR) debug
	$(MAKE) CFLAGS="$(DFLAGS)" all

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BNS_DIR)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BNS)

re: fclean all

.PHONY: all debug bonus debug_bonus clean fclean re
