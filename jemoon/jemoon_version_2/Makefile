NAME = minishell

SRC = main.c \
      syntax/exec_commads_set_tpye/exec_commads_set_tpye.c \
      syntax/exec_commads/exec_commads_liked_list.c \
      syntax/exec_commads/exec_commads_size.c \
	  syntax/exec_commads/exec_commads_size_2.c \
      syntax/exec_commads/get_exec_commads.c \
	  syntax/exec_commads/get_exec_commads_2.c \
	  syntax/printf_utils/printf_utils.c \
	  syntax/set_tpye/set_tpye.c \
	  syntax/validate_syntax/validate_bash_syntax.c \
      syntax/validate_syntax/validate_bash_syntax_utils.c \
	  syntax/validate_syntax/trade_exce_cmd.c \
	  syntax/readline_utils/readline_utils.c \
	  built_in/builtin.c \
	  built_in/check_built_in_cmd/check_built_in_cmd.c \
	  built_in/exit/exit.c \
	  built_in/echo/echo.c \
	  built_in/env/env.c \
	  built_in/pwd/pwd.c \
	  built_in/export/export.c \
	  built_in/export/export_frist.c \
	  built_in/export/export_rest.c \
	  built_in/export/export_sort.c \
	  built_in/export/export_utils.c \
	  built_in/export/export_list_utils.c \
	  liked_list/linked_list.c \
	  resource_free/free_list.c \
	  resource_free/secondary_array_free.c \
	  libft/ft_isalnum.c \
	  libft/ft_isalpha.c \
	  libft/ft_isdigit.c \
	  libft/ft_isspecial_chr.c \
	  libft/ft_itoa.c \
	  libft/ft_split.c \
	  libft/ft_strdup.c \
	  libft/ft_strlen.c \
	  libft/ft_strncmp.c \
	  libft/ft_strcmp.c \
	  libft/secondary_array_len.c \
	  error_process/allocate_error.c \
	  error_process/syntax_error.c \
	  initial/set_environ.c \
	  substitution/chagne_dollar_sign.c \
	  substitution/check_token_quote.c \
	  substitution/copy_n_div_token.c \
	  substitution/split_criteria_dollar_sign.c \
	  substitution/substitution_token.c \
	  utils/utils.c \
	  operator_character_check.c \
	  split_words.c \
	  token_character_check.c \
	  extract_words.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

HEADER = minishell.h

.PHONY: all clean fclean re

all: $(NAME)
	@echo "Compiling $(NAME)..."

$(NAME): $(OBJ)
	@cc $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@cc $(CFLAGS) -c $< -o $@
	
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing executable $(NAME)..."
	@rm -f $(NAME)

re: fclean all
