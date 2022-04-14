# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:17:49 by vkrajcov          #+#    #+#              #
#    Updated: 2022/04/14 10:45:40 by gclausse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS = $(addprefix srcs/, lexer.o)
	#   $(addprefix xx/, xx.o))

LIBFTOBJ = $(addprefix libft/, ft_substr.o ft_strlen.o)

CFLAGS = -Ilibft -Iincludes -Wall -Wextra -Werror
DBFLAGS = -g3 -fsanitize=address

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug: LDFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS) $(LIBFTOBJ)
	$(CC) $(LDFLAGS) $^ -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
