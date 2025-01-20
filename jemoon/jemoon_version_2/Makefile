NAME = minishell

SRC = main.c \
      exec_commads/exec_commads_liked_list.c \
      exec_commads/exec_commads_size.c \
      exec_commads/get_exec_commads.c \
	  exec_commads/get_exec_commads_2.c \
	  printf_utils/printf_utils.c \
	  set_tpye/set_tpye.c \
	  validate_syntax/validate_bash_syntax.c \
      validate_syntax/validate_bash_syntax_utils.c \
	  validate_syntax/trade_exce_cmd.c \
	  liked_list/linked_list.c \
	  readline_utils/readline_utils.c \
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

$(NAME): $(OBJ)
	@cc $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
