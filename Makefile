SRC_FOLDER	= src/
SRC=main.c \
	builtin.c \
	environment.c \
	token.c \
	tokenizer.c \
	lexer.c \
	expander.c \
	commander.c \
	executor.c \
	find_exec.c \
	ft_strldup.c \
	free_strs.c \
	free_shell.c \
	signal.c \

OBJ_FOLDER=objects/
OBJ		= $(addprefix $(OBJ_FOLDER), $(SRC:.c=.o))


CC = clang
FLAGS=-Wall -Wextra -Werror -fsanitize=address

LIBFT_DIR=libft/
LIBFT_LIB=$(LIBFT_DIR)libft.a

PRINTF_DIR=printf/
PRINTF_LIB=$(PRINTF_DIR)libftprintf.a

HEADERS= $(SRC_FOLDER) $(SRC_FOLDER)libshell $(LIBFT_DIR) $(PRINTF_DIR)include/
INCLUDES=$(addprefix -I , $(HEADERS))

LIBS=$(LIBFT_LIB) $(PRINTF_LIB) -lreadline

NAME = minishell

SHELL = bash

RESET	= \x1b[1;0m
BLACK	= \x1b[1;30m
RED	= \x1b[1;31m
GREEN	= \x1b[1;32m
YELLOW	= \x1b[1;33m
BLUE	= \x1b[1;34m
PURPLE	= \x1b[1;35m
CYAN	= \x1b[1;36m
WHITE	= \x1b[1;37m

BORDER_C = $(PURPLE)

OVERLAP = 0

CAT_C = $(PURPLE)
CATE_C = $(RED)

define box
	@tput civis
	$(if $(filter $(3), 0), ,@tput cuu $(3))
	@printf "$(BORDER_C)%s%s%s%16s\n" "╘╪" "─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─" "╪╛" ""
	@printf "%-20s $(1)%-29s$(RESET)$(BORDER_C)%s%16s\n" "╞╫" "$(2)" "╫╡" ""
	@printf "%s%s%s$(RESET)%16s\n" "╒╪" "─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─═─" "╪╕" ""
	@tput cnorm	
endef

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	$(call box, $(YELLOW), $<, 0)
	@mkdir -p $(OBJ_FOLDER)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	$(call box, $(GREEN), $<, $(OVERLAP))

$(NAME): $(LIBS) $(OBJ) | cat
	$(call box, $(YELLOW), BUILDING EXECUTABLE..., 0)
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $@
	$(call box, $(GREEN), BUILDING EXECUTABLE, $(OVERLAP))


$(LIBFT_LIB): | cat
	$(call box, $(YELLOW), BUILDING LIBFT..., 0)
	@make --silent -C $(LIBFT_DIR) bonus
	$(call box, $(GREEN), LIBFT BUILD SUCCESS, $(OVERLAP))

$(PRINTF_LIB): | cat
	$(call box, $(YELLOW), BUILDING PRINTF..., 0)
	@make --silent -C $(PRINTF_DIR)
	$(call box, $(GREEN), PRINTF BUILD SUCCESS, $(OVERLAP))

cat: 
	@echo -e "$(CAT_C)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀ "
	@echo -e "$(CAT_C)⠀⠀⠀⠀⢀⡴⣆⠀⠀⠀⠀⠀⣠⡀⠀⠀⠀⠀⠀⠀⣼⣿⡗⠀⠀⠀⠀"
	@echo -e "$(CAT_C)⠀⠀⠀⣠⠟⠀⠘⠷⠶⠶⠶⠾⠉⢳⡄⠀⠀⠀⠀⠀⣧⣿⠀⠀⠀⠀⠀"
	@echo -e "$(CAT_C)⠀⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣤⣤⣤⣤⣤⣿⢿⣄⠀⠀⠀⠀"
	@echo -e "$(CAT_C)⠀⠀⡇⠀$(CATE_C)x⠀⠀⠀⠀⠀x$(CAT_C)⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⠀⠙⣷⡴⠶⣦"
	@echo -e "$(CAT_C)⠀⠀⢱⡀⠀ ⠉⠉⠀⠀⠀  ⠀⢠⡟⠂⠀⠀⢀⣀⣠⣤⠿⠞⠛⠋"
	@echo -e "$(CAT_C)⣠⠾⠋⠙⣶⣤⣤⣤⣤⣤⣀⣠⣤⣾⣿⠴⠶⠚⠋⠉⠁⠀⠀⠀⠀⠀⠀"
	@echo -e "$(CAT_C)⠛⠒⠛⠉⠉⠀⠀⠀⣴⠟⣣⡴⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo -e "$(CAT_C)⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"

all: $(NAME)

re: cat fclean all

clean: cat 
	$(call box, $(RED), CLEANING, 0)
	@rm -fr $(OBJ_FOLDER)
	@rm -fr $(TARGET)
	@make --silent -C $(LIBFT_DIR) clean
	@make --silent -C $(PRINTF_DIR) clean
	$(call box, $(GREEN), CLEANING, $(OVERLAP))

fclean: cat clean
	$(call box, $(RED), CLEANING LIBS, 0)
	@rm -fr $(NAME)
	@make --silent -C $(LIBFT_DIR) fclean
	@make --silent -C $(PRINTF_DIR) fclean
	$(call box, $(GREEN), CLEANING LIBS, $(OVERLAP))

.PHONY: all re clean fclean cat
