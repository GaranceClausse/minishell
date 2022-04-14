# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkrajcov <vkrajcov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:17:49 by vkrajcov          #+#    #+#              #
#    Updated: 2022/04/14 17:35:46 by vkrajcov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJS = $(addprefix srcs/, main.o)

LIBFT_OBJ = $(addprefix libft/, ft_strcmp.o)

CFLAGS = -Iincludes -Ilibft -Wall -Wextra -Werror
LDFLAGS = -lreadline
DBFLAGS = -g3

all: $(NAME)

debug: CFLAGS+=$(DBFLAGS)
debug: LDFLAGS+=$(DBFLAGS)
debug:	$(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@ 

clean: 
	$(RM) $(OBJS) $(LIBFT_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug