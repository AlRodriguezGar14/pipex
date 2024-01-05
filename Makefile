# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 02:14:31 by alberrod          #+#    #+#              #
#    Updated: 2024/01/05 15:04:15 by alberrod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = cc
HEADERS_DIR = .
CFLAGS   = -Wall -Wextra -Werror -g -I $(HEADERS_DIR)
NAME     = pipex
RM       = rm -rf
#CMD_1	 = "grep ol"
CMD_1	 = "ls -la"

LIBFT_DIR = libft/
CFILES = main.c generate_cmd_list_utils.c parse_inputs.c processes.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) -L $(LIBFT_DIR) -lft
	# ar rcs $(NAME) $(OFILES)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test:
	./pipex hola.txt ${CMD_1} "wc -w" outfile.txt 
.PHONY: all clean fclean re test
 
