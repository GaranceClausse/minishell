# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:17:49 by vkrajcov          #+#    #+#              #
#    Updated: 2022/04/13 17:30:49 by vkrajcov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS = $(addprefix srcs/, main.o)

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
DBFLAGS = -g3 -fsanitize=address

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug: LDFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug