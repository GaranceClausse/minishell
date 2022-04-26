
NAME = minishell
OBJS = 	$(addprefix srcs/, main.o signal.o\
	   	$(addprefix parser/, cmd.o parser.o grammar.o grammar_2.o)\
		$(addprefix lexer/, lexer.o lexer_utils.o get_token.o get_token_type.o) \
		$(addprefix env/, env.o env_utils.o)\
		$(addprefix expander/, ft_split.o spliter.o expander.o))


LIBFTOBJ = $(addprefix libft/, ft_substr.o ft_strlen.o ft_strcmp.o \
	   ft_strncmp.o ft_realloc_str.o ft_strdup.o ft_lstadd_back.o ft_lstclear.o \
	   ft_lstdelone.o ft_lstlast.o ft_lstnew.o ft_swap.o ft_strjoin.o ft_is_in_set.o \
	   free_char_tab)

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
