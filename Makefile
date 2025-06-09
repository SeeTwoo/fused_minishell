
NAME = minishell
LIBFTDIR = libftprintf
FLAGS = -Wall -Werror -Wextra -g3 -Iincludes -I$(LIBFTDIR)/include \
		-I$(LIBFTDIR)/libft
LIBFT = -L$(LIBFTDIR)/libft -lft
PRINTF = -L$(LIBFTDIR) -lftprintf 
READLINE = -I. -lreadline

CC = cc

SRC_DIR = src
OBJ_DIR = obj

SRC := alt_real_expension.c \
	   builtins.c \
	   builtins2.c \
	   builtins_utils.c \
	   check_types.c \
	   check_types2.c \
	   env.c \
	   env_utils.c \
	   error.c \
	   exec.c \
	   exec_cmd_utils.c \
	   exec_path.c \
	   exec_redirection.c \
	   expansion.c \
	   expansion_utils.c \
	   free_all.c \
	   free_ast.c \
	   here_doc.c \
	   here_doc_utils.c \
	   main.c \
	   minishell.c \
	   parsing.c \
	   parsing_utils.c \
	   signals_set.c \
	   signals_handle.c \
	   syntax.c \
	   syntax_utils.c \
	   tokenization.c \
	   tokenization_utils.c \
	   tree_new.c \
	   tree_redirection.c \
	   tree_traverse.c \
	   tree_traverse_utils.c \
	   tree_utils.c \
	   utils.c \
	   pipes.c \
	   wildcards.c \
	   wildcards_matching.c \
	   wildcards_tokens.c \
	   wildcards_utils.c \
	   wildcards_utils2.c

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFTDIR)/libftprintf.a $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFTDIR)/libftprintf.a:
	make -C $(LIBFTDIR)

$(NAME): $(OBJ)	
	$(CC) -g $(OBJ) $(FLAGS) $(LIBFT) $(READLINE) $(PRINTF) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -g $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
