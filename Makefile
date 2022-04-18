# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:17:49 by vkrajcov          #+#    #+#              #
#    Updated: 2022/04/18 12:08:10 by gclausse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS = $(addprefix srcs/, lexer.o lexer_utils.o env.o env_utils.o)
	#   $(addprefix xx/, xx.o))

LIBFTOBJ = $(addprefix libft/, ft_substr.o ft_strlen.o ft_strcmp.o free_char_tab.o \
	   ft_strncmp.o ft_realloc_str.o)

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
