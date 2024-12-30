/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-29 05:11:14 by jahong            #+#    #+#             */
/*   Updated: 2024-12-29 05:11:14 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>    /* readline함수를 사용하기위한 헤더 */
# include <readline/history.h>     /* add_history함수를 사용하기위한 헤더 */
# include <stdio.h>                /* printf함수를 사용하기위한 헤더 */
# include <stdlib.h> 

typedef enum {
    NONE,
    PIPE,
    REDIRECTION,
    CMD,
    OPTION,
    ARG
} t_tokentype;

typedef struct  cmd_list
{
    char			*token;
    t_tokentype     type;
    struct cmd_list *parant;
    struct cmd_list *prev;
    struct cmd_list	*next;
}					t_list;

//void replace_char(char *str);
int     main(void);

/* tokenize_with_quotes.c */
t_list  *split_words(char const *str, int cmd_flag);
t_list *mn_split(char const *str);

/* linked_list.c */
t_list  *create_linked_list(char *str);
void    add_back_linked_list(t_list **tokenize, t_list *new);
void    make_node(t_list **tokenize, char *str);
void	free_linked_list(t_list *list);

#endif