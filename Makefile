# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 02:14:31 by alberrod          #+#    #+#              #
#    Updated: 2024/01/03 03:26:07 by alberrod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = cc
HEADERS_DIR = .
CFLAGS   = -Wall -Wextra -Werror -g -I $(HEADERS_DIR)
NAME     = pipex.a
RM       = rm -rf

CFILES = generate_cmd_list_utils.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test:
	cc main.c pipex.a libft/libft.a && ./a.out hola.txt "ls -l" "wc -w" mundo.txt 
.PHONY: all clean fclean re test
 
