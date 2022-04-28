<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:17:49 by vkrajcov          #+#    #+#              #
#    Updated: 2022/04/18 15:54:24 by gclausse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS = $(addprefix srcs/, lexer.o lexer_utils.o env.o env_utils.o main.o)
	 $(addprefix builtins/, echo.o))
=======

NAME = minishell
OBJS = 	$(addprefix srcs/, main.o signal.o\
	   	$(addprefix parser/, cmd.o parser.o grammar.o grammar_2.o)\
		$(addprefix lexer/, lexer.o lexer_utils.o get_token.o get_token_type.o) \
		$(addprefix env/, env.o env_utils.o)\
		$(addprefix expander/, expander.o expansion.o))
>>>>>>> expand


LIBFTOBJ = $(addprefix libft/, ft_substr.o ft_strlen.o ft_strcmp.o \
	   ft_strncmp.o ft_realloc_str.o ft_strdup.o ft_lstadd_back.o ft_lstclear.o \
	   ft_lstdelone.o ft_lstlast.o ft_lstnew.o ft_swap.o ft_strjoin.o ft_is_in_set.o \
	   free_char_tab.o ft_isalnum.o)

CFLAGS = -Ilibft -Iincludes -Wall -Wextra -Werror
DBFLAGS = -g3
LDFLAGS = -lreadline

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug: LDFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS) $(LIBFTOBJ)
	$(CC) $(LDFLAGS) $^ -o $@ 

clean: 
	$(RM) $(OBJS) $(LIBFTOBJ) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
