SRCS = srcs/main.c srcs/env.c srcs/echo.c srcs/utils.c srcs/utils_exec.c srcs/exec.c srcs/parsing.c srcs/pipe.c srcs/ft_split_parse.c \
	   srcs/parsing_redirec.c srcs/here_doc.c srcs/redirection.c srcs/cd.c srcs/unset.c srcs/export.c srcs/signal.c \
	   srcs/ft_split_parse_two.c srcs/here_doc_two.c srcs/exec_minishell.c srcs/utils_exec_second.c srcs/exit.c srcs/utils_two.c srcs/ft_split_free.c srcs/parsing_redirec_two.c srcs/pwd.c srcs/utils_hd.c

SRCS_BONUS	= 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Iincludes
NAME = minishell
NAME_BONUS =
RM = rm -f
LIBS = -Llibft -lft $(READLINE)
READLINE =  -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include/readline/

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all:  $(NAME)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) -o $(NAME) $(OBJS) $(LIBS) 

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
		make -C libft -s
		$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBS)

debug: CFLAGS+=-g
debug: re

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)
		make clean -C libft

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)
		make fclean -C libft

re: fclean all

.PHONY: all fclean clean re debug bonus
