# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maelmahf <maelmahf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 18:29:04 by oait-h-m          #+#    #+#              #
#    Updated: 2025/06/21 15:16:21 by maelmahf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC= main.c\
parsing/pars_utils1.c \
parsing/pars_utils2.c \
parsing/syntax_error.c \
getenv/get_env.c \
tokenization/type_of_tokens.c \
tokenization/user_input1.c \
tokenization/user_input.c \
tokenization/utils.c \
tokenization/utils1.c \
expansion/expansion_again.c \
expansion/utils1.c \
expansion/utils2.c \
expansion/utils3.c \
expansion/utils4.c \
expansion/utils5.c \
expansion/utils6.c \
expansion/utils7.c \
execution/add_args_to_array.c \
execution/exec.c \
execution/exec_pipe.c \
execution/apply_redirect.c \
execution/update_env.c \
builtins/env.c \
builtins/echo.c \
builtins/pwd.c \
builtins/export.c \
builtins/unset.c \
builtins/cd.c \
builtins/exit.c \
builtins/is_builtins.c \
libft/ft_is_alnum.c \
libft/ft_atoi.c \
libft/ft_is_alpha.c \
libft/ft_is_digits.c \
libft/ft_putstr_fd.c \
libft/ft_strcat.c \
libft/ft_strchr.c \
libft/ft_strcmp.c \
libft/ft_strdup.c \
libft/ft_strncpy.c \
libft/ft_strtok.c \
libft/ft_substr.c \
expansion/expansion_again.c \
gc/garbage_collector.c \
gc/gc_utils.c \
parsing/herdoc.c \
parsing/herdoc_utils1.c


CC= cc 
CFLAGS= -Wall -Wextra -Werror -g3
 #-Wall -Wextra -Werror
 #-fsanitize=address
RFLAG= -lreadline

OBJS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(RFLAG) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
