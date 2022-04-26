NAME = minishell
OBJS = $(addprefix srcs/, env.o env_utils.o main.o\
	   $(addprefix parser/, cmd.o parser.o grammar.o grammar_2.o)\
		 $(addprefix lexer/, lexer.o lexer_utils.o get_token.o get_token_type.o))


LIBFTOBJ = $(addprefix libft/, ft_substr.o ft_strlen.o ft_strcmp.o free_char_tab.o \
	   ft_strncmp.o ft_realloc_str.o ft_strdup.o ft_lstadd_back.o ft_lstclear.o \
	   ft_lstdelone.o ft_lstlast.o ft_lstnew.o ft_swap.o ft_strjoin.o)

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
